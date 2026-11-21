"""Calculate array payload sizes for the benchmark's default test case."""

# ctypes lets Python query the sizes of native types corresponding to the C++ types
import ctypes

# Match the benchmark: R sparse rows, eight stored entries per row,
# and F dense features per row. A has C = 4R columns.
R, NNZ_PER_ROW, F = 32768, 8, 32
C, NNZ = 4 * R, R * NNZ_PER_ROW

# Query native element sizes rather than assuming size_t is always 8 bytes.
# These correspond to the C++ types on the same host/ABI as this Python.
SIZE_T_BYTES = ctypes.sizeof(ctypes.c_size_t)
UINT32_BYTES = ctypes.sizeof(ctypes.c_uint32)
DOUBLE_BYTES = ctypes.sizeof(ctypes.c_double)

# The sizes dictionary stores each array's calculated footprint in bytes.
# payload = element count * bytes per element
sizes = {
    "row_ptr": (R + 1) * SIZE_T_BYTES,
    "col_idx": NNZ * UINT32_BYTES,
    "values": NNZ * DOUBLE_BYTES,
    "X": C * F * DOUBLE_BYTES,
    "Y": R * F * DOUBLE_BYTES,
    "expected": R * F * DOUBLE_BYTES,
}

# Report only array payloads, excluding vector metadata and allocator overhead.
# One mebibyte (MiB) is 2**20 bytes.
for name, size in sizes.items():
    print(f"{name:8s}: {size:12,d} bytes ({size / 2**20:.6f} MiB)")
total = sum(sizes.values())
print(f"{'Total':8s}: {total:12,d} bytes ({total / 2**20:.6f} MiB)")
