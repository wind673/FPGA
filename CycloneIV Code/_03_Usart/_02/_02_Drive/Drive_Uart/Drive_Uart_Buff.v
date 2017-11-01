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
	 ,input [31:0]in_test_Vpp //得到所测的频率
	 ,input in_key
	 
	 ,output out_send_update 
	 ,output [7:0]out_send_byte	
	 ,output [31:0]out_set_freq  //设置频率
	 ,output [15:0]out_set_vpp //设置峰峰值
	 ,output [15:0]out_set_phase //设置相位
	 ,output [15:0]out_set_shifty //设置y轴偏移量
	 ,output out_led
	 
	 
);	
 
	
reg [7:0]receive_buff[0:9];			

reg send_update;
reg receive_buff_flag; 

 
reg [7:0]send_byte;
reg [31:0]set_freq;
reg [15:0]set_vpp;
reg [15:0]set_phase;
reg [15:0]set_shifty;
reg led;

assign out_send_update 		= send_update;
assign out_send_byte 		= send_byte;
assign out_set_freq  		= set_freq;
assign out_set_vpp  			= set_vpp;
assign out_set_phase 		= set_phase;
assign out_set_shifty		= set_shifty;
assign out_led 				= led;

  
reg receive_time_over; 
reg [7:0]receive_cnt;
always @(posedge in_receive_update or negedge in_clr) //接收buff  
begin 

	if(in_clr == 0) 
	begin  
		receive_cnt <= 0; 
		receive_time_over <= 0;
	end
	
	if(in_receive_update == 1)
	begin 
		if(cnt_ms > 30) 
		begin 
				receive_time_over <= 0;//超时 
		end 
	 
		if(receive_time_over == 0)//超时，则是下一帧
		begin
			receive_cnt <= 0;
			receive_buff_flag <= 1;   
		end
		 
		receive_buff[receive_cnt] <= in_receive_byte;//接收数据
	 
		case(receive_cnt) 
			0:receive_buff_flag <= 0;    
			9: begin receive_buff_flag <= 1;led = !led; end //传输完毕  
		endcase
		 
		receive_cnt <= (receive_cnt + 1)%10;
		if(cnt_ms == 0) receive_time_over <= 1;//重新开始计时
		
	end
	
end


reg [15:0] cnt_ms;  
always @(posedge in_clk_ms or negedge in_clr) //接收buff  
begin
	if(in_clr == 0) 
	begin 
		cnt_ms <= 0; 
	end
	 
	if(in_clk_ms == 1)
	begin
		if(receive_time_over == 0) cnt_ms <= 0;//重新计时
		if(cnt_ms < 40)cnt_ms <= cnt_ms + 1;
	end
	
	
end




reg send_start_flag;   
always @(posedge receive_buff_flag or negedge in_clr)  //分析数据 
begin
	if(in_clr == 0)
	begin 
		send_start_flag = 0; 
	end  
	
   if(receive_buff_flag == 1)
	begin
	
		if(send_thread_cnt > 60) begin  send_start_flag <= 0; end//发送一帧完毕	
		if(receive_buff[0] == 8'hAA)
		begin
			case(receive_buff[1])
			1:set_freq   = 	(receive_buff[2]<<24) | (receive_buff[3]<<16) | (receive_buff[4]<<8) | receive_buff[5];//设置频率
			2:set_vpp    = 	(receive_buff[2]<<8) | receive_buff[3];//设置峰峰值
			3:set_phase  = 	(receive_buff[2]<<8) | receive_buff[3];//设置相位 
			4:begin   
					send_buff[0] = 8'hAA; 
					send_buff[1] = 4; 
					send_buff[2] = (in_test_freq >> 24)&&8'hff ; 
					send_buff[3] = (in_test_freq >> 16)&&8'hff ;
					send_buff[4] = (in_test_freq >> 8)&&8'hff ;
					send_buff[5] = (in_test_freq)&&8'hff ; 
					send_start_flag <= 1; //开始发送
			  end//发送所测的频率
			 
			5:begin   
					send_buff[0] = 8'hAA; 
					send_buff[1] = 5; 
					send_buff[2] = (in_test_Vpp >> 24)&&8'hff ; 
					send_buff[3] = (in_test_Vpp >> 16)&&8'hff ;
					send_buff[4] = (in_test_Vpp >> 8)&&8'hff ;
					send_buff[5] = (in_test_Vpp)&&8'hff ; 
					send_start_flag <= 1; //开始发送
			  end//发送所测的频率 
			  
			6:begin   
					send_buff[0] = 8'hAA; 
					send_buff[1] = 111; 
					send_buff[2] = 222; 
					send_buff[3] = 33;
					send_buff[4] = 44;
					send_buff[5] = 55; 
					send_buff[6] = 66; 
					send_buff[7] = 77; 
					send_buff[8] = 88;  
					send_start_flag <= 1; //开始发送
			  end//发送所测的频率 
			 
			endcase
		end
		 
	end
	
end
  
 

reg [7:0]send_thread_cnt; 
reg [7:0]test_cnt; 
reg [7:0]crc; 
reg [7:0]send_buff[0:9];	
always @(posedge in_clk_ms)  //发送10byte数据
begin 
	 
	if(send_start_flag == 1)
	begin
		if(send_thread_cnt < 70) send_thread_cnt <= send_thread_cnt + 1;
		case(send_thread_cnt)
			  0:	begin send_update <= 0;  crc <= 0;end  //0
			  1:	begin send_byte <= send_buff[0]; end	
			  2:	send_update <= 1; 
			  3:  send_update <= 0; 
			   
			  4:	begin send_update <= 0; end  //1
			  5:	begin send_byte <= send_buff[1];crc <= (crc + send_buff[1]*1)%256; end	
			  6:	send_update <= 1; 
			  7:  send_update <= 0; 
			   
			  8:	begin send_update <= 0; end  //2
			  9:	begin send_byte <= send_buff[2]; crc <= (crc + send_buff[2]*2)%256; end	
			  10:	send_update <= 1; 
			  11: send_update <= 0; 
			  
			  12:	begin send_update <= 0; end  //3
			  13:	begin send_byte <= send_buff[3]; crc <= (crc + send_buff[3]*3)%256; end	
			  14:	send_update <= 1; 
			  15: send_update <= 0; 
			  
			  16:	begin send_update <= 0; end  //4
			  17:	begin send_byte <= send_buff[4]; crc <= (crc + send_buff[4]*4)%256;end	
			  18:	send_update <= 1; 
			  19: send_update <= 0; 
			  
			  20:	begin send_update <= 0; end  //5
			  21:	begin send_byte <= send_buff[5]; crc <= (crc + send_buff[5]*5)%256; end	
			  22:	send_update <= 1; 
			  23: send_update <= 0; 
			  
			  24:	begin send_update <= 0; end  //6
			  25:	begin send_byte <= send_buff[6]; crc <= (crc + send_buff[6]*6)%256; end	
			  26:	send_update <= 1; 
			  27: send_update <= 0; 
			  
			  28:	begin send_update <= 0; end  //7
			  29:	begin send_byte <= send_buff[7]; crc <= (crc + send_buff[7]*7)%256; end	
			  30:	send_update <= 1; 
			  31: send_update <= 0; 
			  
			  32:	begin send_update <= 0; end  //8
			  33:	begin send_byte <= send_buff[8]; crc <= (crc + send_buff[8]*8)%256; end		
			  34:	send_update <= 1; 
			  35: send_update <= 0; 
			  
			  36:	begin send_update <= 0; end  //9
			  37:	begin send_byte <= crc; end	
			  38:	send_update <= 1; 
			  39: send_update <= 0;  
			  
	 	endcase 
	end
	else send_thread_cnt = 0;
	
end


 
	
	 

endmodule
 









