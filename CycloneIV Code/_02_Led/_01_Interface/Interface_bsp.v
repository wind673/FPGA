 /*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Interface_bsp.v
* @Description : 顶层接口
* @Date        : 2017/4/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : 接口的终端
*=============================================================================*/   
/* 顶层接口模块 ----------------------*/
module Interface_bsp
( 
	/* Drive_Clock -------------------*/
	input clk_50M 
	,input clr
	
	/* Drive_Led ---------------------*/
	,output [3:0]led_bus
	
);   

/* Drive_Clock ----------------------*/
wire out_clk_us;  
wire out_clk_ms;  
wire out_clk_s; 	

Drive_Clock Drive_Clock0
(  
	.in_clk_50M(clk_50M)
	,.in_clr(clr)
	
	,.out_clk_us(out_clk_us)
	,.out_clk_ms(out_clk_ms) 
	,.out_clk_s(out_clk_s) 
	 
);

 
 
/* Drive_Clock ------------------------*/ 
App_Led App_Led0
(    
	.in_clr(clr) 
	,.in_clk_ms(out_clk_ms) 
	
	,.out_led(led_bus[0])  
	
);

 
 
endmodule
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





  
  
  
  
  
 
  
  