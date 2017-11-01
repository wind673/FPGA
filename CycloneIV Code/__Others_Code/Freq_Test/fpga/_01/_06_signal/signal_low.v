module signal_low (clk_50mhz,signal,data);

input clk_50mhz;
input signal;
output [31:0] data;

wire clk_100mhz;

pll_100mhz (
	.inclk0(clk_50mhz),
	.c0(clk_100mhz)
);

counter_low U2(
.clk_100mhz(clk_100mhz),
.signal(signal),
.data(data)
);
endmodule
