/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : TrafficLight.v
* @Description : 交通灯
* @Date        : 2016/10/27
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE15F23C8)
* @Explain     : None
*=============================================================================*/ 
module TrafficLight
(
	 input in_clk_ms 
	,input in_clr
	,output [23:0]out_ShowData
	,output [3:0]out_led 
	
);

/* 寄存器配置 -------------------------*/
reg [23:0]ShowData;  
reg [31:0]time_ms; 
reg [31:0]time_s; 
reg [3:0]led;
reg [3:0]Led_State; 

/* 运行线程 ---------------------------*/
always @(posedge in_clk_ms,negedge in_clr)
begin   
	if(!in_clr)
	begin                                                                                                     
		time_ms <= 0;
		time_s <= 5;
		Led_State <= 0;
		led <= 4'b1011;
	end

	else 
	begin 
		time_ms <= (time_ms + 1)%1000000; 
		if(time_ms%200 == 0)
		begin  
			if(time_s == 0) 
			begin
				Led_State <= (Led_State + 1)%4; 
				if(Led_State == 0) begin led = 4'b0111; time_s <= 30;end
				else if(Led_State == 1) begin  led = 4'b1011; time_s <= 5;end
				else if(Led_State == 2) begin  led = 4'b1101; time_s <= 30;end
				else if(Led_State == 3) begin  led = 4'b1011; time_s <= 5;end
			end
			ShowData <= time_s; 
			if(time_s > 0)time_s <= time_s - 1;//0~30s循环  
		end
	end 
end 
 

/* 连接输出 ---------------------------*/ 
assign out_ShowData = ShowData; 
assign out_led = led;
 
 
endmodule
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/














