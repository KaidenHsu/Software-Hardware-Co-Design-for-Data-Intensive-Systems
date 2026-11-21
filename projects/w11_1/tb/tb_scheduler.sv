`timescale 1ns/1ps
module tb_scheduler;
    localparam int ROW_W = 4;
    localparam int ROW_COUNT = 16;
    localparam int MAX_CMDS = 64;

    logic clk = 1'b0;
    always #5 clk = ~clk;

    logic rst;
    logic [1:0] head_valid;
    logic [ROW_W-1:0] head_row0, head_row1;
    logic [1:0] issue_valid, pop_count;
    logic [ROW_W-1:0] issue_row0, issue_row1;
    logic [ROW_COUNT-1:0] busy_rows;
    logic [31:0] issued_total, row_hazard_cycles, bank_conflict_cycles;

    dual_issue_scheduler #(.ROW_W(ROW_W), .ROW_COUNT(ROW_COUNT)) dut (
        .clk(clk), .rst(rst),
        .head_valid(head_valid), .head_row0(head_row0), .head_row1(head_row1),
        .issue_valid(issue_valid), .issue_row0(issue_row0), .issue_row1(issue_row1),
        .pop_count(pop_count), .busy_rows(busy_rows),
        .issued_total(issued_total), .row_hazard_cycles(row_hazard_cycles),
        .bank_conflict_cycles(bank_conflict_cycles)
    );

    logic [ROW_W-1:0] trace_mem [0:MAX_CMDS-1];
    int trace_len;

    task automatic load_trace(input int case_id);
        trace_len = 0;
        case (case_id)
            1: begin // From Week 11 Slide 8
                trace_len = 8;
                trace_mem[0]=0; trace_mem[1]=1; trace_mem[2]=0; trace_mem[3]=2;
                trace_mem[4]=3; trace_mem[5]=3; trace_mem[6]=4; trace_mem[7]=5;
            end
            2: begin // Different rows, same bank
                trace_len = 6;
                trace_mem[0]=0; trace_mem[1]=2; trace_mem[2]=4;
                trace_mem[3]=6; trace_mem[4]=8; trace_mem[5]=10;
            end
            3: begin // Same-row dependency chain
                trace_len = 4;
                trace_mem[0]=3; trace_mem[1]=3; trace_mem[2]=3; trace_mem[3]=3;
            end
            4: begin // Command availability gaps
                trace_len = 8;
                trace_mem[0]=0; trace_mem[1]=1; trace_mem[2]=2; trace_mem[3]=3;
                trace_mem[4]=0; trace_mem[5]=4; trace_mem[6]=5; trace_mem[7]=6;
            end
            default: $fatal(1, "Unknown case %0d", case_id);
        endcase
    endtask

    // Testbench drives a two-entry FIFO lookahead, NOT a DMA or full FIFO.
    // Commands are removed ONLY when the scheduler reports pop_count.
    // The oracle below checks every issue decision and counter on every cycle.
    task automatic run_case(input int case_id, input string test_name);
        int ptr;
        int cycles;
        int expected_issued;
        int expected_row_events;
        int expected_bank_events;
        logic [ROW_COUNT-1:0] previous_cycle_issued;
        logic [ROW_COUNT-1:0] new_reservations;
        logic expect0, expect1;
        logic row_event, bank_event;
        logic gap;
        int expected_pop;

        load_trace(case_id);
        rst = 1'b1;
        head_valid = 2'b00;
        head_row0 = '0;
        head_row1 = '0;
        repeat (2) @(posedge clk);
        @(negedge clk);
        rst = 1'b0;

        ptr = 0;
        cycles = 0;
        expected_issued = 0;
        expected_row_events = 0;
        expected_bank_events = 0;
        previous_cycle_issued = '0;

        while (ptr < trace_len) begin
            if (cycles > 50) $fatal(1, "%s: timeout / no forward progress", test_name);
            @(negedge clk);

            // For case 4, testbench hides the FIFO heads in two cycles,
            // modeling intervals when the source FIFO is empty.
            gap = (case_id == 4) && ((cycles == 2) || (cycles == 5));
            head_valid = 2'b00;
            head_row0 = '0;
            head_row1 = '0;
            if (!gap && ptr < trace_len) begin
                head_valid[0] = 1'b1;
                head_row0 = trace_mem[ptr];
                if (ptr + 1 < trace_len) begin
                    head_valid[1] = 1'b1;
                    head_row1 = trace_mem[ptr+1];
                end
            end
            #1; // combinational issue settles

            // Cycle-by-cycle behavioral checker (independent scoreboard).
            expect0 = 1'b0;
            expect1 = 1'b0;
            row_event = 1'b0;
            bank_event = 1'b0;
            if (head_valid[0]) begin
                if (previous_cycle_issued[head_row0]) begin
                    row_event = 1'b1;
                end else begin
                    expect0 = 1'b1;
                    if (head_valid[1]) begin
                        if (previous_cycle_issued[head_row1] || head_row0 == head_row1)
                            row_event = 1'b1;
                        else if (head_row0[0] == head_row1[0])
                            bank_event = 1'b1;
                        else
                            expect1 = 1'b1;
                    end
                end
            end

            expected_pop = (expect0 ? 1 : 0) + (expect1 ? 1 : 0);

            if (issue_valid !== {expect1, expect0})
                $fatal(1, "%s cycle %0d: issue_valid=%b expected=%b", test_name, cycles, issue_valid, {expect1, expect0});
            if (int'(pop_count) != expected_pop)
                $fatal(1, "%s cycle %0d: pop=%0d expected=%0d", test_name, cycles, pop_count, expected_pop);
            if (expect0 && issue_row0 !== head_row0)
                $fatal(1, "%s: lane0 row mismatch", test_name);
            if (expect1 && issue_row1 !== head_row1)
                $fatal(1, "%s: lane1 row mismatch", test_name);

            new_reservations = '0;
            if (expect0) new_reservations[head_row0] = 1'b1;
            if (expect1) new_reservations[head_row1] = 1'b1;

            expected_issued += expected_pop;
            if (row_event) expected_row_events++;
            if (bank_event) expected_bank_events++;

            @(posedge clk);
            #1; // nonblocking assignments settle
            if (busy_rows !== new_reservations)
                $fatal(1, "%s cycle %0d: busy=%h expected=%h", test_name, cycles, busy_rows, new_reservations);
            if (issued_total !== expected_issued)
                $fatal(1, "%s cycle %0d: issued counter mismatch", test_name, cycles);
            if (row_hazard_cycles !== expected_row_events)
                $fatal(1, "%s cycle %0d: row counter mismatch", test_name, cycles);
            if (bank_conflict_cycles !== expected_bank_events)
                $fatal(1, "%s cycle %0d: bank counter mismatch", test_name, cycles);

            previous_cycle_issued = new_reservations;
            ptr += expected_pop;
            cycles++;
        end

        head_valid = 2'b00;
        $display("PASS %-26s cycles=%0d MACs=%0d row_stall=%0d bank_conflict=%0d",
                 test_name, cycles, expected_issued, expected_row_events, expected_bank_events);
    endtask

    initial begin
        rst = 1'b1;
        head_valid = '0;
        head_row0 = '0;
        head_row1 = '0;

        run_case(1, "slide8_combined");
        run_case(2, "same_bank_rows");
        run_case(3, "repeated_row");
        run_case(4, "source_gaps");

        $display("ALL FOUR DIRECTED TESTS PASS");
        $finish;
    end
endmodule
