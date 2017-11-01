/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_ADC.v
* @Description : ADC文件
* @Date        : 2017/5/1
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : ADC文件(9600bps 104us/bit)
*=============================================================================*/ 
module Drive_ADC
(   
	 input in_clr
	 ,input in_clk_us  
	 ,input [9:0]in_ADC_data  
	 
	 ,output reg out_OE    
	 ,output reg out_PD    
	 ,output reg out_CLK   
	 ,output reg [31:0]out_ADC_data    
	 
);	


always @(in_clk_us)
begin
	out_OE <= 0;	
	out_PD <= 0;	
	out_CLK = !in_clk_us;	
	if(in_clk_us)
	begin 
		out_ADC_data[9] = in_ADC_data[0];
		out_ADC_data[8] = in_ADC_data[1];
		out_ADC_data[7] = in_ADC_data[2];
		out_ADC_data[6] = in_ADC_data[3];
		out_ADC_data[5] = in_ADC_data[4];
		out_ADC_data[4] = in_ADC_data[5];
		out_ADC_data[3] = in_ADC_data[6];
		out_ADC_data[2] = in_ADC_data[7];
		out_ADC_data[1] = in_ADC_data[8];
		out_ADC_data[0] = in_ADC_data[9];
	end
	
end
	
	
	
	
	
	
endmodule


/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/













