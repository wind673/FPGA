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
	input in_clk_50M 
	,input in_clr
	,input in_uart_rx 
	,input [4:1]in_key_bus
	,input [10:1]in_ADC_data
	,input in_signal					//***************************
	   
	,output [4:1]out_led_bus
	,output out_uart_tx 
	,output out_ADC_OE 
	,output out_ADC_PD
	,output out_ADC_CLK
	,output [9:0]out_DAC_data
	,output out_DAC_WRT 
	,output out_DAC_CLK
	
);   
 
 
wire w_clk_us;  
wire w_clk_ms;  
wire w_clk_s; 	

//低频模块
wire  [31:0] w_data_low;				//************************

signal_low signal_low
(
.clk_50mhz(in_clk_50M),
.signal(in_signal),
.data(w_data_low)

);

//高频模块
wire  [31:0] w_data;				//************************

signal signal
(
.clk_50mhz(in_clk_50M),
.signal(in_signal),
.data(w_data)

);

//倍频模块


Drive_Clock Drive_Clock0
(  
	.in_clk_50M(in_clk_50M)
	,.in_clr(in_clr)
	
	,.out_clk_us(w_clk_us)
	,.out_clk_ms(w_clk_ms) 
	,.out_clk_s(w_clk_s) 
	 
);

 
  
App_Led App_Led0
(    
	.in_clr(in_clr) 
	,.in_clk_ms(w_clk_ms) 
	
	,.out_led(out_led_bus[1])  
	
);


 
Drive_Usart_Top Drive_Usart_Top
(
	.in_clk_us(w_clk_us)
	,.in_clr(in_clr) 
	,.in_rx(in_uart_rx)
	,.in_key(in_key_bus[1]) 
	,.in_test_Vpp(w_ADC_data) 
	,.in_test_freq(w_data)     //***************************
	,.in_test_freq_low(w_data_low)
	,.out_tx(out_uart_tx)
	,.out_led(out_led_bus[4:2])
	
	
);


wire [31:0]w_ADC_data;
Drive_ADC Drive_ADC
(
	.in_clr(in_clr) 
	,.in_clk(in_clk_50M) 
	,.in_ADC_data(in_ADC_data[10:1])
	
	,.out_OE(out_ADC_OE) 
	,.out_PD(out_ADC_PD) 
	,.out_CLK(out_ADC_CLK) 
	,.out_ADC_data(w_ADC_data) 
	
);
 
Drive_DAC Drive_DAC
(
	.in_clr(in_clr) 
	,.in_clk(in_clk_50M) 
	,.in_ADC_data(in_ADC_data[10:1])
	
	,.out_WRT(out_DAC_WRT)  
	,.out_CLK(out_DAC_CLK) 
	,.out_DAC_data(out_DAC_data) 
	
);


 
endmodule
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/









  
  
  
  
  
 
  
  