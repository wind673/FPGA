module counter_low(clk_100mhz,signal,data);

input clk_100mhz;
input signal;
output reg [31:0] data;

reg [31:0] temp;

always @(posedge clk_100mhz)
	begin
		if(signal==1)
		  temp<=temp+1;
		else
			temp<=0;
	end
always @(negedge signal)
	begin
		data<=temp*2;
	end

endmodule