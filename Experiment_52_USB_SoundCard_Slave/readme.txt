实验器材:
	探索者STM32F4开发板
	
实验目的:
	学习STM32的USB SLAVE功能使用,实现一个USB声卡
	
硬件资源:
	1,DS0(连接在PF9),DS1(连接在PF10)
	2,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模块(通过FSMC驱动,FSMC_NE4接LCD片选/A6接RS)  
	4,USB_SLAVE接口(通过跳线帽将D-/D+连接在PA11/PA12上)
	5,按键KEY0(PE4)/KEY2(PE2)
	6,WM8978音频CODEC芯片(连接关系见STM32F4开发指南,48.2节)
	7,IIS音频接口(用于驱动WM8978)  
	

实验现象:
	本实验代码,开机的时候先显示一些提示信息，之后开始USB配置，在配置成功之后就可以在电脑上
	发现多出一个USB声卡。我们用DS1来指示USB是否连接成功，并在液晶上显示USB连接状况，如果成
	功连接，DS1会亮，此时，我们可以将耳机插入开发板的PHONE端口，听到来自电脑的音频信号，同
	时通过两个按键可以调节音量：按KEY0可以增大音量，KEY2可以减少音量。同样我们还是用DS0来
	指示程序正在运行。 
	
注意事项: 
	1,4.3寸和7寸屏需要比较大电流,USB供电可能不足,请用外部电源适配器(推荐外接12V 1A电源).
	2,本例程在LCD_Init函数里面(在ILI93xx.c),用到了printf,如果不初始化串口1,将导致液晶无法显示!!  
	3,本实验需要用跳线帽短接P11的D+和PA12，以及D-和PA11。
	4,本实验USB_HOST接口不要插任何设备。
	5,请自备耳机一副（非必须）。
	6,本实验开发板配套的T口USB线应该插USB_SLAVE。  


				正点原子@ALIENTEK
				2014-10-25
				广州市星翼电子科技有限公司
				电话：020-38271790
				传真：020-36773971
				购买：http://shop62103354.taobao.com
				http://shop62057469.taobao.com
				公司网站：www.alientek.com
				技术论坛：www.openedv.com
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				