//=================================波特率产生模块=====================================
module speed_select_rx(clk,rst_n,bps_start,clk_bps);//波特率设定
 input clk;   //50M时钟
 input rst_n;  //复位信号
 input bps_start; //接收到信号以后,波特率时钟信号置位,当接收到uart_rx传来的信号以后,模块开始运行
 output clk_bps; //接收数据中间采样点,
 
// `define BPS_PARA 5207;//9600波特率分频计数值
// `define BPS_PARA_2 2603;//计数一半时采样
 
 reg[12:0] cnt;//分频计数器
 reg clk_bps_r;//波特率时钟寄存器
 
 reg[2:0] uart_ctrl;//波特率选择寄存器
 
 always @(posedge clk or negedge rst_n)
  if(!rst_n)
   cnt<=13'd0;
  else if((cnt==5207)|| !bps_start)//判断计数是否达到1个脉宽
   cnt<=13'd0;
  else
   cnt<=cnt+1'b1;//波特率时钟启动
   
 always @(posedge clk or negedge rst_n) begin
  if(!rst_n)
   clk_bps_r<=1'b0;
  else if(cnt== 2603)//当波特率计数到一半时,进行采样存储
   clk_bps_r<=1'b1;
  else
   clk_bps_r<=1'b0;
 end
 assign clk_bps = clk_bps_r;//将采样数据输出给uart_rx模块
 
endmodule



