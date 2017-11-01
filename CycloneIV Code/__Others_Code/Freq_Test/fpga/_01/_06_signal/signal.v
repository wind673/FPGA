module signal(clk_50mhz,signal,data,updata);

input clk_50mhz;
input signal;
output updata;
output [31:0] data;

wire clk_2s;

reg [31:0] temp;

count_2s U1(
.clk_50mhz(clk_50mhz),
.clk_2s(clk_2s)
);

counter U2( 
.clk_1hz(clk_2s),
.signal(signal),
.data(data),
.updata(updata)
);
endmodule

