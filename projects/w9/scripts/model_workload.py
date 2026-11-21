"""Model helpers for the Week 9 signed-integer SpMV lab."""


def mix32(h):
    """Mix an integer into a deterministic unsigned 32-bit hash."""
    h = (h ^ h >> 16) & 0xffffffff
    h = h * 0x7feb352d & 0xffffffff
    h = (h ^ h >> 15) & 0xffffffff
    h = h * 0x846ca68b & 0xffffffff
    return (h ^ h >> 16) & 0xffffffff


def command(op, row=0, col=0, val=0):
    """Pack an opcode, row, local column, and signed value into 64 bits."""
    assert 0 <= op <= 3 and 0 <= row < 32768 and (0 <= col < 2048)
    assert -32768 <= val <= 32767
    return op << 62 | row << 47 | col << 36 | val & 0xffffffff


def unpack(c):
    """Decode a command, interpreting its immediate as signed 32-bit."""
    op = c >> 62 & 3
    row = c >> 47 & 32767
    col = c >> 36 & 2047
    val = c & 0xffffffff
    if val >= 2 ** 31:
        val -= 2 ** 32
    return (op, row, col, val)


def model(commands, rows, tile):
    """Execute commands and check initialization, ordering, and numeric bounds."""

    # The command stream must clear outputs first and drain them exactly once.

    y = [None] * rows
    x = [None] * tile
    have_clear = False
    have_drain = False
    mac = loads = 0

    # Accept loads/MACs only between CLEAR_Y and the final DRAIN_Y.
    for i, c in enumerate(commands):
        op, row, col, val = unpack(c)
        if op == 2:
            assert i == 0 and (not have_clear)
            y = [0] * rows
            have_clear = True
        elif op == 0:
            assert have_clear and (not have_drain) and (col < tile)
            x[col] = val
            loads += 1
        elif op == 1:
            assert have_clear and (not have_drain) and (row < rows) and (col < tile)
            assert x[col] is not None
            y[row] += x[col] * val
            assert -2 ** 31 <= y[row] < 2 ** 31
            mac += 1
        elif op == 3:
            assert i == len(commands) - 1 and have_clear and (not have_drain)
            have_drain = True

    assert have_drain
    return (y, mac, loads)


def gen_case(rows, nzpr, cols, pattern, tile):
    """Generate tile-ordered commands, an independent oracle, and metadata."""

    # Bucket contributions by x tile; retain the original row-indexed oracle.

    assert 1 <= rows <= 32768 and 1 <= nzpr <= 64 and (1 <= cols <= 262144)
    assert 1 <= tile <= 2048 and tile & tile - 1 == 0
    assert pattern in ('clustered', 'scattered')

    # Clustered inputs touch at most one 2048-entry region.
    active = min(2048, cols) if pattern == 'clustered' else cols
    x = [j * 7 % 13 - 6 for j in range(cols)]
    bins = [[] for _ in range((cols + tile - 1) // tile)]
    ref = [0] * rows
    nnz = rows * nzpr
    uniq = set()

    # Build the reference directly while collecting tile-local contributions.
    for k in range(nnz):
        row = k // nzpr
        col = mix32(k ^ 0x9e3779b9) % active
        val = k % 5 - 2
        ref[row] += val * x[col]
        uniq.add(col // 4)
        bins[col // tile].append((row, col % tile, val))
    assert all((-2 ** 31 <= v < 2 ** 31 for v in ref))

    # Load each nonempty x tile once before emitting its MAC commands.
    commands = [command(2)]
    loads = 0
    nonempty = 0
    for tid, b in enumerate(bins):
        if not b:
            continue
        nonempty += 1
        beg = tid * tile
        for j in range(min(tile, cols - beg)):
            commands.append(command(0, col=j, val=x[beg + j]))
            loads += 1
        for row, lcol, val in b:
            commands.append(command(1, row=row, col=lcol, val=val))
    commands.append(command(3))

    # Cross-check the stream model against the original row-wise oracle.
    calculated, mac, loaded = model(commands, rows, tile)
    assert calculated == ref and mac == nnz and (loads == loaded)

    # Optimistic budget excludes external DMA and additional stalls.
    min_cycles = 2 + 3 * rows + loads + 2 * nnz
    return (commands,
        ref,
        {
            'rows': rows,
            'nonzeros_per_row': nzpr,
            'nnz': nnz,
            'cols': cols,
            'pattern': pattern,
            'tile': tile,
            'tiles_nonempty': nonempty,
            'x_loads': loads,
            'x_unique_16B_lines': len(uniq),
            'macs': mac,
            'command_count': len(commands),
            'command_bytes': 8 * len(commands),
            'y_output_bytes': 4 * rows,
            'optimistic_core_cycles': min_cycles,
            'optimistic_core_ms_at_100MHz': round(min_cycles / 100000.0,
                6),
            'x_active_elements': active,
            'numeric_contract': 'int16 x/val, exact int32 y'
        })


def gen_tiny():
    """Build the four-row oracle case and verify its six MAC operations."""
    rp = [0, 2, 3, 5, 6]
    ci = [0, 3, 1, 0, 4, 2]
    val = [2, 1, 3, 4, -1, 5]
    x = [1, 2, 3, 4, 5]

    # Preserve the handout oracle, including its original CSR row boundaries.
    cmds = [command(2)] + [command(0, col=i, val=v) for i, v in enumerate(x)]
    for row in range(4):
        for k in range(rp[row], rp[row + 1]):
            cmds.append(command(1, row=row, col=ci[k], val=val[k]))
    cmds.append(command(3))

    result, nmac, nload = model(cmds, 4, 8)
    assert (result, nmac, nload) == ([6, 6, -1, 15], 6, 5)
    return (cmds, result)
