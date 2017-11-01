module count_2s(clk_50mhz,clk_2s);	//50mhz分频2s，clk50m输入50mhz时钟，clr清零信号，clk输出1hz时钟
	input clk_50mhz;
	output reg clk_2s;
	reg [25:0] countscan;
	always @(posedge clk_50mhz ) 
		begin 
			
			 if(countscan==49999999)
					begin
						countscan<=0;
						clk_2s<=~clk_2s;
					end
					else
						countscan=countscan+1;
		end
endmodule