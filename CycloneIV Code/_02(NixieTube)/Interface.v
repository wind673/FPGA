/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Interface.v
* @Description : 顶层接口
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : None
*=============================================================================*/    
module Interface
( 
	/* Main ---------------------------*/
	input clk_50M, 
	
	/* Nixie_Tube ---------------------*/
	output [7:0]Data,//数码管数据
	output [5:0]Byte//数码管位 
	
);

wire clk_ms;  
wire [23:0]Show_Data;//6位数码管 0 ~ 999999

Main U1
(  
	.in_clk_50M(clk_50M),
	.out_clk_ms(clk_ms),
	.out_Show_Data(Show_Data)
	
);	


NixieTube U2
(  
	.in_Show_Data(Show_Data),
	.in_clk_ms(clk_ms),
	.out_Data(Data),
	.out_Byte(Byte)
	
);
 
 
 
 
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
  
  
  
  
  
 
  
  