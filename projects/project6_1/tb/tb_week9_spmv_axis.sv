`timescale 1ns/1ps
// Four-row signed-arithmetic smoke test with periodic output backpressure.
module tb_spmv_axis;
    logic clk = 0;
    always #5 clk = ~clk;

    // Input driver and output monitor share a 10 ns simulation clock.
    logic rst_n = 0;
    logic [63:0] s_data = 0;
    logic s_valid = 0;
    wire s_ready;
    logic s_last = 0;
    wire [31:0] m_data;
    wire [3:0] m_keep;
    wire m_valid, m_last;
    logic m_ready = 0;
    wire [31:0] nmac, nload, cycles;

    // The fixed oracle includes a negative result to exercise signed arithmetic.
    integer captured = 0;
    integer total_cycles = 0;
    integer exp_y[0:3] = '{6,6,-1,15};

    // Remember stalled beats and verify they survive through the accepting edge.
    logic stalled_prev = 0;
    logic [31:0] stalled_data = 0;
    logic stalled_last = 0;

    // Debug counters independently check accepted load and MAC commands.
    week9_spmv_axis #(.N_ROWS(4), .TILE(8)) dut(
        .aclk(clk), .aresetn(rst_n), .s_axis_tdata(s_data),
        .s_axis_tvalid(s_valid), .s_axis_tready(s_ready), .s_axis_tlast(s_last),
        .m_axis_tdata(m_data), .m_axis_tkeep(m_keep),
        .m_axis_tvalid(m_valid), .m_axis_tready(m_ready),
        .m_axis_tlast(m_last), .dbg_mac_accepted(nmac),
        .dbg_load_accepted(nload), .dbg_cycles(cycles));

    // Pack fields exactly as the software command encoder does.
    function automatic logic [63:0] cmd(
            input logic [1:0] op, input integer row, input integer col,
            input integer value);
        logic [63:0] t;
        t = 64'b0;
        t[63:62] = op;
        t[61:47] = 15'(row);
        t[46:36] = 11'(col);
        t[31:0] = 32'(value);
        return t;
    endfunction

    // Drive on falling edges and hold valid/data until a rising-edge handshake.
    // Drop valid between calls to exercise gaps in the input stream.
    task automatic send(input logic [63:0] command, input logic last);
        @(negedge clk);
        s_data = command;
        s_last = last;
        s_valid = 1;
        do @(posedge clk); while (!s_ready);
        @(negedge clk);
        s_valid = 0;
        s_last = 0;
    endtask

    // Insert two output stall slots per five-cycle period.
    always @(negedge clk) if (rst_n)
        m_ready <= ((total_cycles % 5) != 1) && ((total_cycles % 5) != 2);

    // Check stability, each accepted row, byte enables, and the final-row marker.
    always @(posedge clk) if (rst_n) begin
        total_cycles <= total_cycles + 1;
        if (stalled_prev && (!m_valid || m_data !== stalled_data || m_last !== stalled_last))
            $fatal(1,"Output changed while stalled");

        stalled_prev <= m_valid && !m_ready;
        if (m_valid && !m_ready) begin
            stalled_data <= m_data;
            stalled_last <= m_last;
        end

        if (m_valid && m_ready) begin
            if (captured >= 4 || $signed(m_data) !== exp_y[captured] || m_keep !== 4'hf)
                $fatal(1,"Output mismatch at %0d: %0d",captured,$signed(m_data));
            if (m_last !== (captured == 3)) $fatal(1,"Incorrect TLAST");
            captured <= captured + 1;
        end

        // Bound simulation duration so a deadlock fails instead of hanging.
        if (total_cycles > 500) $fatal(1,"Timeout");
    end

    // Clear y, load x, issue six MACs, and drain the complete four-row oracle.
    initial begin
        repeat(3) @(negedge clk);
        rst_n = 1;
        send(cmd(2,0,0,0),0); // clear all row accumulators
        for (int j=0; j<5; j++) send(cmd(0,0,j,j+1),0);

        // Contributions are sent without precomputing their products on the host.
        send(cmd(1,0,0, 2),0);
        send(cmd(1,0,3, 1),0);
        send(cmd(1,1,1, 3),0);
        send(cmd(1,2,0, 4),0);
        send(cmd(1,2,4,-1),0);
        send(cmd(1,3,2, 5),0);
        send(cmd(3,0,0, 0),1); // trigger output stream

        // Wait for accepted outputs before checking operation accounting.
        wait (captured==4);
        @(negedge clk);
        if (nmac !== 6 || nload !== 5)
            $fatal(1,"Counter mismatch MAC=%0d LOAD=%0d",nmac,nload);
        $display("W9_VERILATOR_SPMV=PASS rows=4 mac=6 y=[6,6,-1,15] cycles=%0d",cycles);
        $finish;
    end
endmodule
