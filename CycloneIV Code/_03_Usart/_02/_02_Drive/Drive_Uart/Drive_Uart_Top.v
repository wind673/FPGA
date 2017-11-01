/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Uart_Top.v
* @Description : 串口顶层文件
* @Date        : 2017/4/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : None
*=============================================================================*/ 
module Drive_Uart_Top
(
	 input in_clk_50M    
	 ,input in_clr 
	 ,input in_clk_ms
	 ,input in_rx 
	 ,input in_key
	 
	 ,output out_tx  
	 ,output out_led  
	 
	 
);		
		


wire w_clk; 
wire w_busy;
clkdiv clkdiv
(
	.clk50(in_clk_50M)
	,.rst_n(in_clr)
	,.clkout(w_clk)
	
);



wire w_receive_update; 
wire [7:0]w_receive_byte;
uart_rx  uart_rx//数据接收模块
(    
   .clk(w_clk)
   ,.rst_n(in_clr)
   ,.rx(in_rx) 
	,.dataout(w_receive_byte) 
	,.rdsig(w_receive_update)
);
 
     
  
wire w_send_update;
wire [7:0]w_send_byte;	
uart_tx  uart_tx//数据发送模块
(  
	.clk(w_clk)
	,.rst_n(in_clr) 
	,.datain(w_send_byte)
	,.update(w_send_update)
	,.busy(w_busy)
	,.tx(out_tx)
	
);
		
		
		

Drive_Uart_Buff  Drive_Uart_Buff		
(  
	.in_clk_ms(in_clk_ms)
	,.in_clr(in_clr) 
	,.in_receive_update(w_receive_update)
	,.in_send_busy(w_busy)
	,.in_receive_byte(w_receive_byte)
	,.in_key(in_key)
	
	,.out_send_update(w_send_update)
	,.out_send_byte(w_send_byte)
	,.out_led(out_led)
	
	
); 


	
	
endmodule











