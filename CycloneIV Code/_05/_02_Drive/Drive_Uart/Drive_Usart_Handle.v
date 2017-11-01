/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Usart_Handle.v
* @Description : 串口处理文件
* @Date        : 2017/5/1
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Quartus II 15.0 (64-bit) (EP4CE22E22C8)
* @Explain     : 处理帧数据
*=============================================================================*/ 
module Drive_Usart_Handle
(   
	 input in_clr 
	 ,input in_clk_us  
	 ,input in_receive_update 
	 ,input [7:0]in_receive_byte 
	 ,input in_key
	 ,input [31:0]in_test_freq
	 ,input [31:0]in_test_Vpp
	 
	 ,output reg out_send_update 
	 ,output reg [7:0]out_send_byte 
	 ,output reg [3:2]out_led 
	 ,output reg [31:0]out_set_freq  //设置频率
	 ,output reg [15:0]out_set_vpp //设置峰峰值
	 ,output reg [15:0]out_set_phase //设置相位
	 ,output reg [15:0]out_set_shifty //设置y轴偏移量
	 
	 
);




/* 运行线程 ---------------------------*/ 
reg [7:0]receive_buff[0:10];	 
reg receive_buff_flag;  
reg [7:0]receive_cnt;
reg [7:0]receive_crc; 
reg receive_us_reload;
always @(posedge in_receive_update) //接收buff  
begin     
	 
	 if(receive_us > 10000)  
		receive_cnt <= 0;//时间越界，下一帧   
	 else 
		receive_cnt <= receive_cnt + 1;//时间没有越界
	  
	 receive_buff[receive_cnt] <= in_receive_byte;
	 if(receive_cnt < 9) receive_crc <= (receive_crc + receive_buff[receive_cnt]*receive_cnt)%256;
	 
	 case(receive_cnt)
		0:	begin receive_crc <= 0;	receive_buff_flag = 0;end  
		8: receive_buff_flag = 1;	
		9:	begin    
				receive_buff_flag = 0;
				out_led[2] = !out_led[2]; 
			end 
	 endcase  
	 
	 receive_us_reload <= !receive_us_reload;//重新计时
end



reg [31:0]receive_us; 
reg receive_us_reload_last;
always @(posedge in_clk_us) 
begin
	
	if(receive_us < 1000000) receive_us <= receive_us + 1;	
	
	if(receive_us_reload != receive_us_reload_last)	receive_us <= 0;//重新计时
	receive_us_reload_last <= receive_us_reload;	
	
	
end






reg send_start_flag;   
always @(receive_buff_flag)  //分析数据 
begin     
		if(send_state) begin send_start_flag <= 0; end//发送一帧完毕		
		if(receive_buff_flag)
		case(receive_buff[1])
		
			/* 设置频率 */  
			1:begin 
				out_set_freq <= (receive_buff[2]<<24) | (receive_buff[3]<<16) | (receive_buff[4]<<8) | receive_buff[5];
				send_buff[0] <= 8'hAA; 
				send_buff[1] <= receive_buff[1];  
				send_buff[2] <= receive_buff[2]; 
				send_buff[3] <= receive_buff[3];
				send_buff[4] <= receive_buff[4];
				send_buff[5] <= receive_buff[5]; 
				send_buff[6] <= receive_buff[6]; 
				send_buff[7] <= receive_buff[7]; 
				send_buff[8] <= receive_buff[8];  
				send_start_flag <= 1;  
				 
			end
			
			/* 设置峰峰值 */  
			2:begin
				out_set_vpp <= (receive_buff[2]<<8) | receive_buff[3];
				send_buff[0] <= 8'hAA; 
				send_buff[1] <= receive_buff[1];  
				send_buff[2] <= receive_buff[2]; 
				send_buff[3] <= receive_buff[3];
				send_buff[4] <= receive_buff[4];
				send_buff[5] <= receive_buff[5]; 
				send_buff[6] <= receive_buff[6]; 
				send_buff[7] <= receive_buff[7]; 
				send_buff[8] <= receive_buff[8];  
				send_start_flag <= 1; //开始发送
				
			end
			
			/* 设置相位 */
			3:begin
				out_set_phase  <= (receive_buff[2]<<8) | receive_buff[3];
				send_buff[0] <= 8'hAA; 
				send_buff[1] <= receive_buff[1];  
				send_buff[2] <= receive_buff[2]; 
				send_buff[3] <= receive_buff[3];
				send_buff[4] <= receive_buff[4];
				send_buff[5] <= receive_buff[5]; 
				send_buff[6] <= receive_buff[6]; 
				send_buff[7] <= receive_buff[7]; 
				send_buff[8] <= receive_buff[8];  
				send_start_flag <= 1; //开始发送 
			end
			
			/* 获取所测频率 */
			4:begin    
				send_buff[0] <= 8'hAA; 
				send_buff[1] <= 4; 
				send_buff[2] <= (in_test_freq >> 24)&8'hff; 
				send_buff[3] <= (in_test_freq >> 16)&8'hff;
				send_buff[4] <= (in_test_freq >> 8)&8'hff;
				send_buff[5] <= (in_test_freq)&8'hff ; 
				send_buff[6] <= 0;
				send_buff[7] <= 0;
				send_buff[8] <= 0; 
				send_start_flag <= 1; //开始发送
				
			 end
			 
			/* 获取所测电压 */ 
			5:begin   
				send_buff[0] <= 8'hAA; 
				send_buff[1] <= 5; 
				send_buff[2] <= (in_test_Vpp >> 24)&8'hff; 
				send_buff[3] <= (in_test_Vpp >> 16)&8'hff;
				send_buff[4] <= (in_test_Vpp >> 8)&8'hff;
				send_buff[5] <= (in_test_Vpp)&8'hff;
				send_buff[6] <= 0;
				send_buff[7] <= 0;
				send_buff[8] <= 0;
				send_start_flag <= 1; //开始发送
				
			 end//发送所测的频率  
			 
			/* 测试使用 */ 				
//			default:begin    
//					send_buff[0] <= 8'hAA; 
//					send_buff[1] <= receive_buff[1];  
//					send_buff[2] <= receive_buff[2]; 
//					send_buff[3] <= receive_buff[3];
//					send_buff[4] <= receive_buff[4];
//					send_buff[5] <= receive_buff[5]; 
//					send_buff[6] <= receive_buff[6]; 
//					send_buff[7] <= receive_buff[7]; 
//					send_buff[8] <= receive_buff[8];  
//					send_start_flag <= 1; //开始发送
//							
//				end 
		endcase
		
	 
	
	
end



reg [31:0]send_thread_cnt;   
reg [7:0]send_crc; 
reg [7:0]send_buff[0:9];	 
reg send_state;
always @(posedge in_clk_us)  //发送10byte数据
begin    
	if(send_start_flag == 1) send_state <= 1;
	
	if(send_state)
	begin 
		case(send_thread_cnt)
			  1:	begin out_send_update <= 0;  send_crc <= 0;out_led[3] <= ~out_led[3]; end  //0
			  1000:	begin out_send_byte <= send_buff[0]; end	
			  2000:	out_send_update <= 1; 
			  2100:  out_send_update <= 0; 
			   
			  5000:	begin out_send_update <= 0; end  //1
			  6000:	begin out_send_byte <= send_buff[1];send_crc <= (send_crc + send_buff[1]*1)%256; end	
			  7000:	out_send_update <= 1; 
			  7100:  out_send_update <= 0; 
			   
			  10000:	begin out_send_update <= 0; end  //2
			  11000:	begin out_send_byte <= send_buff[2]; send_crc <= (send_crc + send_buff[2]*2)%256; end	
			  12000:	out_send_update <= 1; 
			  12100: out_send_update <= 0; 
			  
			  15000:	begin out_send_update <= 0; end  //3
			  16000:	begin out_send_byte <= send_buff[3]; send_crc <= (send_crc + send_buff[3]*3)%256; end	
			  17000:	out_send_update <= 1; 
			  17100: out_send_update <= 0; 
			  
			  20000:	begin out_send_update <= 0; end  //4
			  21000:	begin out_send_byte <= send_buff[4]; send_crc <= (send_crc + send_buff[4]*4)%256;end	
			  22000:	out_send_update <= 1; 
			  22100: out_send_update <= 0; 
			  
			  25000:	begin out_send_update <= 0; end  //5
			  26000:	begin out_send_byte <= send_buff[5]; send_crc <= (send_crc + send_buff[5]*5)%256; end	
			  27000:	out_send_update <= 1; 
			  27100: out_send_update <= 0; 
			  
			  30000:	begin out_send_update <= 0; end  //6
			  31000:	begin out_send_byte <= send_buff[6]; send_crc <= (send_crc + send_buff[6]*6)%256; end	
			  32000:	out_send_update <= 1; 
			  32100: out_send_update <= 0; 
			  
			  35000:	begin out_send_update <= 0; end  //7
			  36000:	begin out_send_byte <= send_buff[7]; send_crc <= (send_crc + send_buff[7]*7)%256; end	
			  37000:	out_send_update <= 1; 
			  37100: out_send_update <= 0; 
			  
			  40000:	begin out_send_update <= 0; end  //8
			  41000:	begin out_send_byte <= send_buff[8]; send_crc <= (send_crc + send_buff[8]*8)%256; end		
			  42000:	out_send_update <= 1; 
			  42100: out_send_update <= 0; 
			  
			  45000:	begin out_send_update <= 0; end  //9
			  46000:	begin out_send_byte <= send_crc; end	
			  47000:	out_send_update <= 1; 
			  47100: out_send_update <= 0;   
			  47101: begin send_thread_cnt = 0;send_state <= 0;end
	 	endcase  
		if(send_state) send_thread_cnt = send_thread_cnt + 1; 
	end
end









endmodule

/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
 