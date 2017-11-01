/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_ADC.v
* @Description : DAC文件
* @Date        : 2017/5/1
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : DAC文件 
*=============================================================================*/ 
module Drive_DAC
(   
	 input in_clr
	 ,input in_clk   
	 ,input [9:0]in_ADC_data
	 
	 ,output reg out_WRT     
	 ,output reg out_CLK   
	 ,output reg [9:0]out_DAC_data  
	  
	 
);	


always @(in_clk)
begin  
	out_CLK <= in_clk;	
	out_WRT <= in_clk;	
	if(!in_clk)
	begin 
		//芯片是这样的 
//		out_DAC_data[9] <= in_ADC_data[0];//符号位
		out_DAC_data[8] <= in_ADC_data[1];
		out_DAC_data[7] <= in_ADC_data[2];
		out_DAC_data[6] <= in_ADC_data[3];
		out_DAC_data[5] <= in_ADC_data[4];
		out_DAC_data[4] <= in_ADC_data[5];
		out_DAC_data[3] <= in_ADC_data[6];
		out_DAC_data[2] <= in_ADC_data[7];
		out_DAC_data[1] <= in_ADC_data[8];
		out_DAC_data[0] <= in_ADC_data[9]; 
		out_DAC_data[9] <= in_ADC_data[0];//符号位s
	end
	
end
	
	
	
	
	
	
endmodule


/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/













