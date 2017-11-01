/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : NixieTube.v
* @Description : 数码管
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : 数码管驱动程序
*=============================================================================*/    
module NixieTube
(
	input [23:0]in_ShowData,//6位数码管 0 ~ 999999
	input in_clk_ms,
	
	output [7:0]out_Data,//数码管数据
	output [5:0]out_Byte//数码管位 
	
);   

/* 寄存器配置 -------------------------*/
reg [3:0]Temp_Num; 
reg [2:0]Temp_Byte; 
reg [5:0]Byte;
reg [7:0]Data;

/* 参数设置 ---------------------------*/  
parameter _0 = 8'b1100_0000, _1 = 8'b1111_1001, _2 = 8'b1010_0100, 
	       _3 = 8'b1011_0000, _4 = 8'b1001_1001, _5 = 8'b1001_0010, 
			 _6 = 8'b1000_0010, _7 = 8'b1111_1000, _8 = 8'b1000_0000,
			 _9 = 8'b1001_0000;


/* 运行线程 ---------------------------*/ 
always @(posedge in_clk_ms)
begin
	Temp_Byte <= (Temp_Byte + 1)%6;//6位数码管 
	Temp_Num <= Exchange_To_ByteNum(in_ShowData,Temp_Byte); 
	
	Byte <= Exchange_To_NixieByte(Temp_Byte);//选择位(板子上用了三极管反向了)   
	Data <= Exchange_To_NixieNum(Temp_Num);//显示该位数据  
end
 


/* 函数编写 ---------------------------*/
function[5:0] Exchange_To_NixieByte;//转换成数码管位
input[2:0]  Byte;//输入位  
begin
case(Byte)
	0:Exchange_To_NixieByte = 6'b11_1110;
	1:Exchange_To_NixieByte = 6'b11_1101;
	2:Exchange_To_NixieByte = 6'b11_1011;
	3:Exchange_To_NixieByte = 6'b11_0111;
	4:Exchange_To_NixieByte = 6'b10_1111;
	5:Exchange_To_NixieByte = 6'b01_1111;
	default:Exchange_To_NixieByte = 6'b11_1111;
endcase 
end 
endfunction


function[3:0] Exchange_To_ByteNum;//转换成单个10进制数
input[23:0] Fun_Data;//输入数据 
input[2:0]  Fun_Byte;//输入位  
begin
case(Fun_Byte)
	0:Exchange_To_ByteNum = (Fun_Data/1)%10;
	1:Exchange_To_ByteNum = (Fun_Data/10)%10; 
	2:Exchange_To_ByteNum = (Fun_Data/100)%10; 
	3:Exchange_To_ByteNum = (Fun_Data/1000)%10; 
	4:Exchange_To_ByteNum = (Fun_Data/10000)%10; 
	5:Exchange_To_ByteNum = (Fun_Data/100000)%10; 
	default:Exchange_To_ByteNum = 0;
endcase 
end 
endfunction


function[7:0] Exchange_To_NixieNum;//转换成数码管数
input[3:0] Fun_Num;//输入单个10进制数 
begin 
case(Fun_Num)
	0:Exchange_To_NixieNum = _0; 
	1:Exchange_To_NixieNum = _1; 
	2:Exchange_To_NixieNum = _2; 
	3:Exchange_To_NixieNum = _3; 
	4:Exchange_To_NixieNum = _4; 
	5:Exchange_To_NixieNum = _5; 
	6:Exchange_To_NixieNum = _6; 
	7:Exchange_To_NixieNum = _7; 
	8:Exchange_To_NixieNum = _8; 
	9:Exchange_To_NixieNum = _9; 
	default:Exchange_To_NixieNum = 0;  
endcase 
end 
endfunction



/* 连接输出 ---------------------------*/
assign out_Byte = Byte;
assign out_Data = Data;


endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/ 

 


 