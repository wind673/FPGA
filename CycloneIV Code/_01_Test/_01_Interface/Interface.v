 /*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Interface.v
* @Description : 顶层接口
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : 接口的终端
*=============================================================================*/    
module Interface
( 
	/* Main ---------------------------*/
	input clk_50M,
	input clr,
	
	/* Led ----------------------------*/ 
	output [3:0]led//4位LED灯			
		
);


/* 安置接口线 -------------------------*/
wire clk_us;  
wire clk_ms;  
wire clk_s;    


/* 连接各接口 -------------------------*/
Clock Drive_Clock
(  
	.in_clk_50M(clk_50M),
	.out_clk_us(clk_us),
	.out_clk_ms(clk_ms),
	
	
	.out_clk_s(clk_s) 
);	
 
 
Led App_Led
(
	.in_clk_ms(clk_ms)
	 
);



 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
  
  
  
  
  
 
  
  