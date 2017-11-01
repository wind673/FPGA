`timescale 1ns / 1ps//时钟精度

module LED (
    clk, // 开发板上输入时钟: 50Mhz
    rst_n, // 开发板上输入复位按键
    led // 输出 LED 灯,用于控制开发板上四个 LED(   LED1~LED4)
);
//=====================================================
// PORT declarations
//=====================================================
input clk;
input rst_n;
output reg [3:0] led;

//寄存器定义
reg [31:0] timer;

//=====================================================
// 计数器计数:循环计数 0~4 秒
//=====================================================
always @(posedge clk or negedge rst_n) //检测时钟的上升沿和复位的下降沿
begin 

	if (~rst_n) //复位信号低有效
		timer = 0; //计数器清零
		
	else if (timer == 32'd50_000_000)//1.5s*50M = 75M
	begin
      timer = 0;
   end
	
   else
      timer = timer + 1'b1; //计数器加 1
		
end

//=====================================================
// LED 灯控制
//=====================================================
always @(posedge clk or negedge rst_n) //检测时钟的上升沿和复位的下降沿
begin
	
	if (~rst_n) //复位信号低有效
		led = 4'b0000; //LED 灯输出全为高，四个 LED 灯亮
		
   else if (timer == 0) //计数器计到 0 秒，
		led = 4'b1110; //LED4 点亮
		
	else if (timer == 32'd10_000_000) //计数器计到 0.20 秒，
		led = 4'b1101; //LED1 点亮
		
	else if (timer == 32'd20_000_000) //计数器计到 0.40 秒，
		led = 4'b1011; //LED2 点亮
		
	else if (timer == 32'd30_000_000) //计数器计到 0.60 秒，
		led = 4'b0111; //LED3 点亮
		
   else if (timer == 32'd40_000_000) //计数器计到 0.80秒，
		led = 4'b1111; //LED 全灭
	
end

	

	
endmodule








