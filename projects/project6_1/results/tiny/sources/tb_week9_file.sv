`timescale 1ns/1ps
// File-driven output oracle for the generated board-sized stream.
module tb_spmv_file #(
    // The runner overrides these parameters from the workload manifest.
    parameter int N_ROWS = 1024,
    parameter int TILE = 2048,
    parameter int CMD_COUNT = 8194
);
    logic clk=0;
    always #5 clk=~clk;

    // Clock/reset and input/output stream signals.
    logic rst_n=0;
    logic [63:0] s_data='0;
    logic s_valid=0;
    logic s_last=0;
    wire s_ready;
    wire [31:0] m_data;
    wire [3:0] m_keep;
    wire m_valid, m_last;
    logic m_ready=0;
    wire [31:0] nmac,nload,cycles;

    // Memory images contain the full command stream and one oracle word per row.
    logic [63:0] commands [0:CMD_COUNT-1];
    logic [31:0] expected [0:N_ROWS-1];
    integer received=0;
    integer cycle_count=0;

    // Retain the previous stalled payload for stability assertions.
    logic stalled_prev=0;
    logic [31:0] stalled_data='0;
    logic stalled_last=0;

    week9_spmv_axis #(.N_ROWS(N_ROWS),.TILE(TILE)) dut(
        .aclk(clk),.aresetn(rst_n),.s_axis_tdata(s_data),
        .s_axis_tvalid(s_valid),.s_axis_tready(s_ready),.s_axis_tlast(s_last),
        .m_axis_tdata(m_data),.m_axis_tkeep(m_keep),.m_axis_tvalid(m_valid),
        .m_axis_tready(m_ready),.m_axis_tlast(m_last),
        .dbg_mac_accepted(nmac),.dbg_load_accepted(nload),.dbg_cycles(cycles)
    );

    // Run from the workload directory so these relative memory paths resolve.
    initial begin
        $readmemh("cmds.memh",commands);
        $readmemh("expected.memh",expected);
        repeat(3) @(negedge clk);
        rst_n=1;

        // Keep each command valid until accepted; only the final command has TLAST.
        for (int i=0; i<CMD_COUNT; i++) begin
            @(negedge clk);
            s_data=commands[i];
            s_last=(i==CMD_COUNT-1);
            s_valid=1;
            do @(posedge clk); while(!s_ready);
        end

        // Stop driving after the final command, then wait for all output rows.
        @(negedge clk);
        s_valid=0;
        s_last=0;
        wait(received==N_ROWS);
        @(negedge clk);

        // CLEAR_Y and DRAIN_Y account for the two non-load/non-MAC commands.
        if(nmac!==((CMD_COUNT-2)-nload))
            $fatal(1,"Input count accounting violation MAC=%0d LOAD=%0d CMD=%0d",nmac,nload,CMD_COUNT);
        $display("W9_FILE_RTL=PASS rows=%0d macs=%0d xloads=%0d cycles=%0d",N_ROWS,nmac,nload,cycles);
        $finish;
    end

    // Deassert ready in two slots per seven-cycle period to force output stalls.
    always @(negedge clk) if(rst_n)
        m_ready <= ((cycle_count % 7) != 2) && ((cycle_count % 7) != 3);

    // Validate stable stalled beats and compare every accepted output in order.
    always @(posedge clk) if(rst_n) begin
        cycle_count <= cycle_count+1;
        if(stalled_prev && (!m_valid || m_data!==stalled_data || m_last!==stalled_last))
            $fatal(1,"Output payload changed under backpressure");

        stalled_prev<=m_valid&&!m_ready;
        if(m_valid&&!m_ready) begin
            stalled_data<=m_data;
            stalled_last<=m_last;
        end

        if(m_valid&&m_ready) begin
            if(received>=N_ROWS || m_data!==expected[received] || m_keep!==4'hf ||
                    m_last!==(received==N_ROWS-1))
                $fatal(1,"Mismatch at row %0d, got=%0d expected=%0d",received,$signed(m_data),$signed(expected[received]));
            received<=received+1;
        end

        // Scale the watchdog with workload size to detect stalled progress.
        if(cycle_count > 10*CMD_COUNT+10*N_ROWS+10000) $fatal(1,"Simulation timeout");
    end
endmodule
