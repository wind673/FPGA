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
	 ,output [1:0]out_led
	 
	 
);	
 
	
reg [7:0]receive_buff[0:9];			

reg send_update;
reg receive_buff_flag; 

 
reg [7:0]send_byte;
reg [31:0]set_freq;
reg [15:0]set_vpp;
reg [15:0]set_phase;
reg [15:0]set_shifty;
reg [1:0]led;

assign out_send_update 	= send_update;
assign out_send_byte 	= send_byte;
assign out_set_freq  	= set_freq;
assign out_set_vpp  		= set_vpp;
assign out_set_phase 	= set_phase;
assign out_set_shifty	= set_shifty;
assign out_led 			= led;

  
reg receive_time_over; 
reg [7:0]receive_cnt;
reg [7:0]receive_crc;
always @(posedge in_receive_update or negedge in_clr) //接收buff  
begin 
	
	if(in_clr == 0) 
	begin  
		receive_cnt <= 0; 
		receive_time_over <= 0;
		receive_crc <= 0; 
	end
	
	if(in_receive_update == 1)
	begin 
		led[0] <= ~led[0];
		if(cnt_ms > 10) 
		begin 
				receive_time_over <= 0;//超时 
		end 
	 
		if(receive_time_over == 0)//超时，则是下一帧
		begin
			receive_cnt <= 0;
			receive_buff_flag <= 0; 
			receive_crc	<= 0;

		end
		 
		receive_buff[receive_cnt] <= in_receive_byte;//接收数据
		if(receive_cnt > 0)
			if(receive_cnt < 9)
				receive_crc <= (receive_crc + receive_buff[receive_cnt])&256;
		
		case(receive_cnt) 
			0:begin receive_buff_flag <= 0;receive_crc <= 0;end    
			9:begin 
					if(receive_cnt == receive_buff[9])
					begin
						receive_buff_flag <= 1; 
					end
			  end //传输完毕  
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
		else if(cnt_ms < 40)cnt_ms <= cnt_ms + 1;
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
		
		if(send_thread_cnt > 60) begin  send_start_flag = 0; end//发送一帧完毕	
		if(receive_buff[0] == 8'hAA)
		begin
			case(receive_buff[1])
			1:set_freq   = 	(receive_buff[2]<<24) | (receive_buff[3]<<16) | (receive_buff[4]<<8) | receive_buff[5];//设置频率
			2:set_vpp    = 	(receive_buff[2]<<8) | receive_buff[3];//设置峰峰值
			3:set_phase  = 	(receive_buff[2]<<8) | receive_buff[3];//设置相位 
			4:begin   
					if(send_start_flag == 0)
					begin
						send_buff[0] = 8'hAA; 
						send_buff[1] = 4; 
						send_buff[2] = (in_test_freq >> 24)&&8'hff ; 
						send_buff[3] = (in_test_freq >> 16)&&8'hff ;
						send_buff[4] = (in_test_freq >> 8)&&8'hff ;
						send_buff[5] = (in_test_freq)&&8'hff ; 
						send_buff[6] = 0;
						send_buff[7] = 0;
						send_buff[8] = 0; 
					send_start_flag = 1; //开始发送
					end
			  end//发送所测的频率
			 
			5:begin   
					if(send_start_flag == 0)
					begin
						send_buff[0] = 8'hAA; 
						send_buff[1] = 5; 
						send_buff[2] = (in_test_Vpp >> 24)&&8'hff; 
						send_buff[3] = (in_test_Vpp >> 16)&&8'hff;
						send_buff[4] = (in_test_Vpp >> 8)&&8'hff;
						send_buff[5] = (in_test_Vpp)&&8'hff;
						send_buff[6] = 0;
						send_buff[7] = 0;
						send_buff[8] = 0;
						send_start_flag = 1; //开始发送
					end
			  end//发送所测的频率 
			  
			6:begin   
					if(send_start_flag == 0)
					begin    
						 send_buff[0] = 8'hAA; 
						 send_buff[1] = 11;  
						 send_buff[2] = 22; 
						 send_buff[3] = 33;
						 send_buff[4] = 44;
						 send_buff[5] = 55; 
						 send_buff[6] = 66; 
						 send_buff[7] = 77; 
						 send_buff[8] = 88;  
						 send_start_flag = 1; //开始发送
					 end//发送所测的频率 
				end 
			endcase
		end
		 
	end
	
end
  
 

reg [7:0]send_thread_cnt; 
reg [7:0]test_cnt; 
reg [7:0]send_crc; 
reg [7:0]send_buff[0:9];	
always @(posedge in_clk_ms)  //发送10byte数据
begin 
	led[1] <= ~led[1]; 
	if(send_start_flag == 1)
	begin
		if(send_thread_cnt < 100) send_thread_cnt <= send_thread_cnt + 1;
		
		case(send_thread_cnt)
			  0:	begin send_update <= 0;  send_crc <= 0;end  //0
			  1:	begin send_byte <= send_buff[0]; end	
			  2:	send_update <= 1; 
			  3:  send_update <= 0; 
			   
			  5:	begin send_update <= 0; end  //1
			  6:	begin send_byte <= send_buff[1];send_crc <= (send_crc + send_buff[1]*1)%256; end	
			  7:	send_update <= 1; 
			  8:  send_update <= 0; 
			   
			  10:	begin send_update <= 0; end  //2
			  11:	begin send_byte <= send_buff[2]; send_crc <= (send_crc + send_buff[2]*2)%256; end	
			  12:	send_update <= 1; 
			  13: send_update <= 0; 
			  
			  15:	begin send_update <= 0; end  //3
			  16:	begin send_byte <= send_buff[3]; send_crc <= (send_crc + send_buff[3]*3)%256; end	
			  17:	send_update <= 1; 
			  18: send_update <= 0; 
			  
			  20:	begin send_update <= 0; end  //4
			  21:	begin send_byte <= send_buff[4]; send_crc <= (send_crc + send_buff[4]*4)%256;end	
			  22:	send_update <= 1; 
			  23: send_update <= 0; 
			  
			  25:	begin send_update <= 0; end  //5
			  26:	begin send_byte <= send_buff[5]; send_crc <= (send_crc + send_buff[5]*5)%256; end	
			  27:	send_update <= 1; 
			  28: send_update <= 0; 
			  
			  30:	begin send_update <= 0; end  //6
			  31:	begin send_byte <= send_buff[6]; send_crc <= (send_crc + send_buff[6]*6)%256; end	
			  32:	send_update <= 1; 
			  33: send_update <= 0; 
			  
			  35:	begin send_update <= 0; end  //7
			  36:	begin send_byte <= send_buff[7]; send_crc <= (send_crc + send_buff[7]*7)%256; end	
			  37:	send_update <= 1; 
			  38: send_update <= 0; 
			  
			  40:	begin send_update <= 0; end  //8
			  41:	begin send_byte <= send_buff[8]; send_crc <= (send_crc + send_buff[8]*8)%256; end		
			  42:	send_update <= 1; 
			  43: send_update <= 0; 
			  
			  45:	begin send_update <= 0; end  //9
			  46:	begin send_byte <= send_crc; end	
			  47:	send_update <= 1; 
			  48: send_update <= 0;  
			  
	 	endcase 
	end
	else send_thread_cnt = 0;
	
end


 
	
	 

endmodule
 









