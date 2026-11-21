// WEEK 11 STUDENT SCAFFOLD -- YOUR IMPLEMENTATION GOES HERE.
// This compiles but intentionally FAILS the functional tests until completed.
// Implement the issue controller, row scoreboard, and event counters.
module dual_issue_scheduler #(
    parameter int ROW_W = 4,
    parameter int ROW_COUNT = 16
) (
    input  logic clk,
    input  logic rst,

    input  logic [1:0] head_valid,
    input  logic [ROW_W-1:0] head_row0,
    input  logic [ROW_W-1:0] head_row1,

    output logic [1:0] issue_valid,
    output logic [ROW_W-1:0] issue_row0,
    output logic [ROW_W-1:0] issue_row1,

    output logic [1:0] pop_count,
    output logic [ROW_COUNT-1:0] busy_rows,
    output logic [31:0] issued_total,
    output logic [31:0] row_hazard_cycles,
    output logic [31:0] bank_conflict_cycles
);
    logic row_stall_event;
    logic bank_conflict_event;

    assign issue_row0 = head_row0;
    assign issue_row1 = head_row1;

    // TODO A (~15 min): Combinational issue logic.
    // - Respect strict FIFO order: do not issue head1 unless head0 issues.
    // - Issue head0 if valid and NOT busy.
    // - Issue head1 if valid, not busy, DIFFERENT row, DIFFERENT bank.
    // - Bank(row) = row[0] (equivalently row modulo 2).
    // - If the first head is blocked, issue neither.
    // - Flag one row_stall_event if either head is blocked by a row hazard.
    // - Otherwise flag bank_conflict_event if head1 is blocked by its bank.
    // - pop_count is 0, 1, or 2, equal to number of asserted issue_valid bits.
    always_comb begin
        issue_valid = 2'b00;
        pop_count = 2'd0;
        row_stall_event = 1'b0;
        bank_conflict_event = 1'b0;
        // YOUR IMPLEMENTATION HERE
        // Head 1 can issue only after head 0 has cleared its row check.
        if (head_valid[0]) begin
            if (busy_rows[head_row0]) begin
                row_stall_event = 1'b1;
            end else begin
                issue_valid[0] = 1'b1;

                if (head_valid[1]) begin
                    // Classify a row hazard before checking the bank.
                    if (busy_rows[head_row1] || head_row0 == head_row1) begin
                        row_stall_event = 1'b1;
                    end else if (head_row0[0] == head_row1[0]) begin
                        bank_conflict_event = 1'b1;
                    end else begin
                        issue_valid[1] = 1'b1;
                    end
                end
            end
        end

        // Widen each lane bit so the sum can represent two issues.
        pop_count = {1'b0, issue_valid[0]} + {1'b0, issue_valid[1]};
    end

    // TODO B (~10 min): Sequential scoreboard and statistics.
    // Reset counters/busy_rows to zero.
    // On each non-reset edge:
    // 1. busy_rows reflects exactly the rows issued THIS cycle; the old
    //    busy_rows is used combinationally to block the current cycle.
    //    Thus row issued in cycle t cannot issue at t+1 but may at t+2.
    // 2. issued_total increases by pop_count.
    // 3. row_hazard_cycles increases by one if row_stall_event asserted.
    // 4. bank_conflict_cycles increases by one if bank_conflict_event asserted.
    always_ff @(posedge clk) begin
        if (rst) begin
            busy_rows <= '0;
            issued_total <= '0;
            row_hazard_cycles <= '0;
            bank_conflict_cycles <= '0;
        end else begin
            // YOUR IMPLEMENTATION HERE
            logic [ROW_COUNT-1:0] next_busy_rows;

            // Replace the previous reservations with this cycle's issues.
            next_busy_rows = '0;
            if (issue_valid[0]) next_busy_rows[head_row0] = 1'b1;
            if (issue_valid[1]) next_busy_rows[head_row1] = 1'b1;
            busy_rows <= next_busy_rows;

            // Count accepted commands and at most one event per category.
            issued_total <= issued_total + {30'b0, pop_count};
            if (row_stall_event) row_hazard_cycles <= row_hazard_cycles + 32'd1;
            if (bank_conflict_event) bank_conflict_cycles <= bank_conflict_cycles + 32'd1;
        end
    end
endmodule
