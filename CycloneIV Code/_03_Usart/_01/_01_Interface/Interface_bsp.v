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
	input in_clk_50M 
	,input in_clr
	,input in_uart_rx
	 
	/* Drive_Led ---------------------*/
	,output [3:0]out_led_bus
	,output out_uart_tx
	
);   

/* Drive_Clock ----------------------*/
wire w_clk_us;  
wire w_clk_ms;  
wire w_clk_s; 	

Drive_Clock Drive_Clock0
(  
	.in_clk_50M(in_clk_50M)
	,.in_clr(in_clr)
	
	,.out_clk_us(w_clk_us)
	,.out_clk_ms(w_clk_ms) 
	,.out_clk_s(w_clk_s) 
	 
);

 
 
/* Drive_Clock ------------------------*/ 
App_Led App_Led0
(    
	.in_clr(in_clr) 
	,.in_clk_ms(w_clk_ms) 
	
	,.out_led(out_led_bus[0])  
	
);



/* Drive_Uart_Top --------------------*/ 
Drive_Uart_Top Drive_Uart_Top0
(
	.in_clk_50M(in_clk_50M)
	,.in_clr(in_clr)
	,.in_clk_ms(w_clk_ms)
	,.in_rx(in_uart_rx)
	
	,.out_tx(out_uart_tx)
	
);



 
endmodule
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/









  
  
  
  
  
 
  
  