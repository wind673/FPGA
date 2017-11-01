/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Clock.v
* @Description : 时钟文件
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : 提供us、ms、s的时钟信号源
*=============================================================================*/ 
module Clock
(
	 input in_clk_50M     
	,output out_clk_us 
	,output out_clk_ms 
	,output out_clk_s 
	
);
 
/* 寄存器配置 -------------------------*/
reg [31:0]time_20ns;//20ns级的计时器
reg clk_us;//us级的时钟 
reg clk_ms;//ms级的时钟 
reg clk_s;//s级的时钟 


/* 运行线程 ---------------------------*/
always @(posedge in_clk_50M)
begin 
	 time_20ns <= (time_20ns + 1)%500000000; 
	 if(time_20ns%(50/2) == 0) clk_us <= ~clk_us;
	 if(time_20ns%(50000/2) == 0) clk_ms <= ~clk_ms; 
	 if(time_20ns == (50000000/2)) clk_s <= ~clk_s; 
	 
end 
 

/* 连接输出 ---------------------------*/
assign out_clk_us = clk_us; 
assign out_clk_ms = clk_ms;  
assign out_clk_s = clk_s;  
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/














