/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Main.v
* @Description : None
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : None
*=============================================================================*/ 
module Main
(
	input in_clk_50M,   
	
	output out_clk_ms,//ms级的时钟   
	output [23:0]out_Show_Data
	
);
 
reg [23:0]clk_s;//s级的时钟 
reg [63:0]clk_20ns;//ns级的时钟 
reg [23:0]Show_Data;
reg clk_ms;


always @(posedge in_clk_50M)
begin 
	 clk_20ns <= (clk_20ns + 1)%100000000;
	 if(clk_20ns%(50000/2) == 0) clk_ms <= ~clk_ms;
	 if(clk_20ns == 50000000) clk_s <= (clk_s + 1)%1000000; 
	
	 
end 


always @(clk_s)
begin  
	 Show_Data = clk_s%10000;	
 
	 
end 


/* 连接输出 ---------------------------*/
assign out_clk_ms = clk_ms; 
assign out_Show_Data = Show_Data; 
 
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/














