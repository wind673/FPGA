 /*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Interface.v
* @Description : 顶层接口
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : 接口的终端
*=============================================================================*/    
module Interface
( 
	/* Main ---------------------------*/
	input clk_50M 
	,input clr
	
	/* Nixie_Tube ---------------------*/
	,output [7:0]NixieTube_Data//数码管数据
	,output [5:0]NixieTube_Byte//数码管位 
	,output [3:0]led//4位LED灯
);

/* 安置接口线 -------------------------*/
wire clk_us;  
wire clk_ms;  
wire clk_s;   
wire [23:0]ShowData;//6位数码管 0 ~ 999999

/* 连接各接口 -------------------------*/
Clock Drive1
(  
	.in_clk_50M(clk_50M)
	,.out_clk_us(clk_us)
	,.out_clk_ms(clk_ms) 
	,.out_clk_s(clk_s)
	
);	


NixieTube Drive2
(  
	.in_ShowData(ShowData)
	,.in_clk_ms(clk_ms)
	,.out_Data(NixieTube_Data)
	,.out_Byte(NixieTube_Byte)
	
);
 
TrafficLight App1
(
	.in_clk_ms(clk_ms)
	,.out_ShowData(ShowData)
	,.in_clr(clr)
	,.out_led(led)
	
);
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
  
  
  
  
  
 
  
  