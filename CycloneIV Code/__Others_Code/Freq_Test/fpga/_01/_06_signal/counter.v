module counter(clk_1hz,signal,data,updata);

input clk_1hz;
input signal;
output reg updata;
output reg [31:0] data;
 

reg [31:0] temp;

	

always @(posedge signal)
	begin
	  if(clk_1hz==1)
		temp<=temp+1;
	  else
		begin
			temp<=0;
      end 	
	end

always @(negedge clk_1hz)
	begin
		data<=temp;
	end

endmodule
