/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Uart_Buff.v
* @Description : 串口缓存
* @Date        : 2017/4/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : None
*=============================================================================*/ 
module Drive_Uart_Buff
(  
	 input in_clk_ms 
	 ,input in_clr 
	 ,input in_receive_update 
	 ,input in_send_busy
	 ,input [7:0]in_receive_byte 
	 ,input [31:0]in_test_freq //得到所测的频率
	 
	 ,output out_send_update 
	 ,output [7:0]out_send_byte	
	 ,output [31:0]out_set_freq  //设置频率
	 ,output [15:0]out_set_vpp //设置峰峰值
	 ,output [15:0]out_set_phase //设置相位
	 ,output [15:0]out_set_shifty //设置y轴偏移量
	 
);	
 
	
reg [7:0]receive_buff[0:9];			
reg receive_cnt;
reg send_update;
reg receive_buff_flag; 
reg [15:0] cnt_ms;
reg erro_time_over;  
reg [7:0]send_byte;
reg [31:0]set_freq;
reg [15:0]set_vpp;
reg [15:0]set_phase;
reg [15:0]set_shifty;

assign out_send_update 		= send_update;
assign out_send_byte 		= send_byte;
assign out_set_freq  		= set_freq;
assign out_set_vpp  			= set_vpp;
assign out_set_phase 		= set_phase;
assign out_set_shifty		= set_shifty;
	  
	  
always @(posedge in_receive_update or posedge in_clk_ms or negedge in_clr) //接收buff  
begin 

	if(in_clr == 0) 
	begin 
		cnt_ms <= 0;
		erro_time_over <= 0;
		receive_cnt <= 0;
	end
	
	else if(in_clk_ms == 1) 
	begin
		cnt_ms <= (cnt_ms + 1)%1000;
		if(cnt_ms > 200) 
		begin 
			erro_time_over <= 1;
			cnt_ms <= 0;
		end 
		
	end 
	
	else if(in_receive_update == 1)
	begin
		if(erro_time_over == 1)//超时，则是下一帧
		begin
			receive_cnt <= 0;
			receive_buff_flag <= 0;  
			erro_time_over <= 0;
		end
		
		if(receive_cnt == 0)
		begin
			receive_buff_flag <= 0;  
		end
		
		else if(receive_cnt == 9)
		begin
			receive_buff_flag = 1;  //传输完毕
		end
		 
		receive_buff[receive_cnt] <= in_receive_byte;//接受数据
		 
		receive_cnt <= (receive_cnt + 1)%10;
		cnt_ms <= 0;//重新计时
		
	end
	
end


reg send_start_flag; 
always @(posedge receive_buff_flag or negedge in_clr)  //分析数据 
begin
	if(in_clr == 0)
	begin 
		send_start_flag = 0;
		send_start_flag  =  ~send_start_flag;//测试用，记得删除
	end
	
	else if(receive_buff_flag == 1)
	begin
		if(receive_buff[0] == 8'hAA)
		begin
			case(receive_buff[1])
			1:set_freq   = 	(receive_buff[2]<<24) | (receive_buff[3]<<16) | (receive_buff[4]<<8) | receive_buff[5];//设置频率
			2:set_vpp    = 	(receive_buff[2]<<8) | receive_buff[3];//设置峰峰值
			3:set_phase  = 	(receive_buff[2]<<8) | receive_buff[3];//设置相位
			4:set_shifty = 	(receive_buff[2]<<8) | receive_buff[3];//设置y轴偏移量 
			5:send_start_flag  =  ~send_start_flag;//发送所测的频率
			
			endcase
		end
		 
	end
	
end
 
 
always @(send_start_flag)  //发送10byte数据
begin

	send_update <= 0;
	
	while(in_send_busy); //等待空闲  0 
	send_byte <= 8'hAA;  
	send_update <= 1;  
	send_update <= 0; 
	
	while(in_send_busy); //等待空闲  1
	send_byte <= 5;  //发送所测频率的指令码
	send_update <= 1;  
	send_update <= 0;
	
	while(in_send_busy); //等待空闲  2
	send_byte <= in_test_freq[31:24];  
	send_update <= 1;  
	send_update <= 0;
	 
	while(in_send_busy); //等待空闲  3
	send_byte <= in_test_freq[23:16];  
	send_update <= 1;  
	send_update <= 0; 
 
	while(in_send_busy); //等待空闲  4
	send_byte <= in_test_freq[15:8];  
	send_update <= 1;  
	send_update <= 0; 
	
	while(in_send_busy); //等待空闲  5
	send_byte <= in_test_freq[7:0];  
	send_update <= 1;  
	send_update <= 0; 
	 
	while(in_send_busy); //等待空闲  6
	send_byte <= 0;  
	send_update <= 1;  
	send_update <= 0; 
	
	while(in_send_busy); //等待空闲  7
	send_byte <= 0;  
	send_update <= 1;  
	send_update <= 0; 
	
	while(in_send_busy); //等待空闲  8
	send_byte <= 0;  
	send_update <= 1;  
	send_update <= 0; 
	
	while(in_send_busy); //等待空闲  9
	send_byte <= 0;  
	send_update <= 1;  
	send_update <= 0; 
	 
end
  
  
  

endmodule
 









