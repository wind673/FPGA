/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Interface.v
* @Description : 接口
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : None
*=============================================================================*/    
module Interface
(  
	Nixie_Show_Data,
	clock_ms,
	Nixie_Data,
	Nixie_Byte,
);
 
output[23:0] Nixie_Show_Data; 
output clock_ms;
output[7:0] Nixie_Data;
output[5:0] Nixie_Byte;

Main U1
( 
	.Nixie_Show_Data(Nixie_Show_Data),
	.clock_ms(clock_ms),
	.Nixie_Data(Nixie_Data),
	.Nixie_Byte(Nixie_Byte),
	
);


NixieTube U2
( 
	.Nixie_Show_Data(Nixie_Show_Data),
	.Nixie_clk_ms(clock_ms),
	.Nixie_Data(Nixie_Data),
	.Nixie_Byte(Nixie_Byte),
	
);
 
 
 
 
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
  
 
  
  