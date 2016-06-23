module simple (
inp1,
inp2,
iccad_clk,
out
);

// Start PIs
input inp1;
input inp2;
input iccad_clk;

// Start POs
output out;
output aaa[0];
output o_imm32[0];

// Start wires
wire n1,
    n10;
wire [3:0] bus1, 
    bus2;
wire [3:0] bus3;
wire n2;
wire n3;
wire n4;
wire inp1;
wire inp2;
wire iccad_clk;
wire out;
wire lcb1_fo;
wire aaa[1];

// Start cells
NAND2_X1 u1/reg0 ( .a(inp1), .b(inp2), .o(n1) );
NOR2_X1 u2 ( .a(n1), .b(n3), .o(n2) );
DFF_X80 f1 ( .d(n2), .ck(lcb1_fo), .q(n3) );
INV_X1 u3 ( .a(n3), .o(n4) );
INV_X1 u4 ( .a(n4), .o(out) );
INV_Z80 lcb1 ( .a(iccad_clk), .o(lcb1_fo) );
DFFPOSX1 o_interrupt_vector_sel_reg[0] ( .D(n3861), .Q(o_interrupt_vector_sel[0]) );

endmodule
