`timescale 1ns/1ps
// Week 9 teaching prototype: one-lane, signed-integer, vector-tiled SpMV engine.
// Architecturally intended for XC7Z020/PYNQ-Z2; timing/resources NOT yet measured.
// 64-bit input command: opcode[63:62], row[61:47], local_x[46:36],
// reserved[35:32]=0, signed_data[31:0].
// 00 LOAD_X; 01 MAC; 10 CLEAR_Y; 11 DRAIN_Y.
// Input data and matrix values must fit signed 16 bits; sums must fit signed 32 bits.
// The PS pre-buckets CSR nonzeros by x tile; the PL never gathers x from PS DDR.
// Input commands are accepted only in READY; output rows use a separate handshake.
module week9_spmv_axis #(
    parameter int N_ROWS = 4,
    parameter int TILE = 8
)(
    input  logic         aclk,
    input  logic         aresetn,

    input  logic [63:0]  s_axis_tdata,
    input  logic         s_axis_tvalid,
    output logic         s_axis_tready,
    input  logic         s_axis_tlast,

    output logic [31:0]  m_axis_tdata,
    output logic [3:0]   m_axis_tkeep,
    output logic         m_axis_tvalid,
    input  logic         m_axis_tready,
    output logic         m_axis_tlast,

    output logic [31:0]  dbg_mac_accepted,
    output logic [31:0]  dbg_load_accepted,
    output logic [31:0]  dbg_cycles
);

    // Address widths remain legal even for a single row or x entry.
    localparam int ROW_W = (N_ROWS < 2) ? 1 : $clog2(N_ROWS);
    localparam int X_W   = (TILE < 2) ? 1 : $clog2(TILE);
    localparam logic [ROW_W-1:0] LAST_ROW = ROW_W'(N_ROWS - 1);

    // A MAC reads RAM in READY and writes the accumulated result one clock later.
    typedef enum logic [2:0] {
        READY = 3'd0,
        CLEAR_Y = 3'd1,
        MAC_WRITE = 3'd2,
        OUT_READ = 3'd3,
        OUT_VALID = 3'd4
    } state_t;
    state_t state;

    // Request block RAM inference; synthesis must confirm the actual mapping.
    (* ram_style = "block" *) logic signed [31:0] ymem [0:N_ROWS-1];
    (* ram_style = "block" *) logic signed [15:0] xmem [0:TILE-1];

    // Pipeline registers retain the accepted MAC operands and destination row.
    logic [ROW_W-1:0] row_q, row_idx;
    logic signed [15:0] a_q, x_q;
    logic signed [31:0] y_q, out_q;
    logic [1:0] opcode;
    logic [14:0] input_row;
    logic [10:0] input_col;
    logic signed [15:0] input_val;

    // Decode the teaching command format; the immediate must sign-extend int16.
    assign opcode = s_axis_tdata[63:62];
    assign input_row = s_axis_tdata[61:47];
    assign input_col = s_axis_tdata[46:36];
    assign input_val = s_axis_tdata[15:0];

    // Hold input off during clear, writeback, and output drain.
    assign s_axis_tready = aresetn && (state == READY);
    assign m_axis_tvalid = aresetn && (state == OUT_VALID);
    assign m_axis_tdata = out_q;
    assign m_axis_tkeep = 4'hf;
    assign m_axis_tlast = (row_idx == LAST_ROW);

// Simulation-only guards reject parameters outside the command field widths.
`ifndef SYNTHESIS
    initial begin
        if (N_ROWS < 1 || N_ROWS > 32768 || TILE < 1 || TILE > 2048)
            $fatal(1, "Unsupported N_ROWS or TILE; command fields are row[14:0], col[10:0]");
    end
`endif

    // Reset control registers only. CLEAR_Y initializes y RAM before use,
    // and LOAD_X supplies each tile; omitting RAM resets supports BRAM inference.
    always_ff @(posedge aclk) begin
        if (!aresetn) begin
            state <= READY;
            row_q <= '0;
            row_idx <= '0;
            a_q <= '0;
            x_q <= '0;
            y_q <= '0;
            out_q <= '0;
            dbg_mac_accepted <= 0;
            dbg_load_accepted <= 0;
            dbg_cycles <= 0;
        end else begin
            dbg_cycles <= dbg_cycles + 1;

            case (state)
                READY: if (s_axis_tvalid && s_axis_tready) begin
                    case (opcode)
                        2'b00: begin // load one element of the current x tile
`ifndef SYNTHESIS
                            if (int'(input_col) >= TILE ||
                                    s_axis_tdata[31:16] != {16{input_val[15]}})
                                $fatal(1, "LOAD_X index/width violation");
`endif
                            xmem[input_col[X_W-1:0]] <= input_val;
                            dbg_load_accepted <= dbg_load_accepted + 1;
                        end

                        // Capture synchronous x/y reads; MAC_WRITE blocks subsequent input
                        // until this update commits, including repeated writes to one row.
                        2'b01: begin // reads are registered; the write follows next cycle
`ifndef SYNTHESIS
                            if (int'(input_row) >= N_ROWS || int'(input_col) >= TILE ||
                                    s_axis_tdata[31:16] != {16{input_val[15]}})
                                $fatal(1, "MAC index/width violation");
`endif
                            row_q <= input_row[ROW_W-1:0];
                            a_q <= input_val;
                            x_q <= xmem[input_col[X_W-1:0]];
                            y_q <= ymem[input_row[ROW_W-1:0]];
                            dbg_mac_accepted <= dbg_mac_accepted + 1;
                            state <= MAC_WRITE;
                        end

                        // Clear every result row, including rows with no contributions.
                        2'b10: begin
`ifndef SYNTHESIS
                            if (s_axis_tlast) $fatal(1, "CLEAR_Y cannot terminate command stream");
`endif
                            row_idx <= '0;
                            dbg_mac_accepted <= 0;
                            dbg_load_accepted <= 0;
                            state <= CLEAR_Y;
                        end

                        // DRAIN_Y terminates input and begins row-ordered output reads.
                        2'b11: begin
`ifndef SYNTHESIS
                            if (!s_axis_tlast) $fatal(1, "DRAIN_Y must be final input command");
`endif
                            row_idx <= '0;
                            state <= OUT_READ;
                        end
                    endcase
                end

                // Clear one row per clock while s_axis_tready remains low.
                CLEAR_Y: begin
                    ymem[row_idx] <= '0;
                    if (row_idx == LAST_ROW) begin
                        row_idx <= '0;
                        state <= READY;
                    end else row_idx <= row_idx + 1'b1;
                end

                // Commit the registered read/modify/write before accepting another MAC.
                MAC_WRITE: begin
                    // The signed 16x16 product yields a signed 32-bit result.
                    // The host asserts that the final and partial sums do not overflow.
                    ymem[row_q] <= y_q + ($signed(a_q) * $signed(x_q));
                    state <= READY;
                end

                // Register a RAM row before exposing it as a valid output beat.
                OUT_READ: begin
                    out_q <= ymem[row_idx];
                    state <= OUT_VALID;
                end

                // Advance only on acceptance. During stalls, out_q and row_idx hold,
                // keeping TDATA and TLAST stable until the receiver is ready.
                OUT_VALID: if (m_axis_tvalid && m_axis_tready) begin
                    if (row_idx == LAST_ROW) state <= READY;
                    else begin
                        row_idx <= row_idx + 1'b1;
                        state <= OUT_READ;
                    end
                end
`ifndef SYNTHESIS
                default: $fatal(1,"Illegal state");
`endif
            endcase
        end
    end
endmodule
