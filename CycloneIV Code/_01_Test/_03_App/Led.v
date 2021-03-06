/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Led.v
* @Description : Led灯
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : Led的App程序
*=============================================================================*/ 
/* 设置接口 ---------------------------*/
module Led
(
	 input in_clk_ms    
	 
);
 
/* 寄存器配置 -------------------------*/
reg [3:0]led;//LED灯
reg [3:0]cnt;

/* 连接输出 ---------------------------*/ 

/* 运行线程 ---------------------------*/
always @(posedge in_clk_ms)
begin
	led = 1 << cnt;
	cnt = (cnt + 1)%4;
	
	
end   


endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/







