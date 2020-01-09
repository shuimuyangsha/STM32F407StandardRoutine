#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include  "probe_scope_cfg.h"
#include  "probe_scope.h"
#include "math.h"

//ALIENTEK 探索者STM32F407开发板 实验1
//跑马灯实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int16_t DebugleftS, DebugrightS;
int16_t DebugSet_leftS =0, DebugSet_rightS =0;
int16_t DebugleftReadSpeed = 0, DebugrightReadSpeed = 0;
char DebugSwitch = 1;
char DebugSwitchChangeFlag = 1;
char DebugMotor_PowerState = 1;
char  DebugStepFlag = 0;
int  DebugGetLED_State1 = -1000;
unsigned int Debug_time;
float Debug_x = 0;
float Debug_y = 0;
float Debug_A = 1;
int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	ProbeScope_Init(1000000);
	
  /**下面是通过直接操作库函数的方式实现IO控制**/	
	
	while(1)
	{
		ProbeScope_Sampling();
		Debug_time++;
		if(Debug_time == 100){
			Debug_time = 0;
			
			Debug_A += 0.1;			
			if(Debug_A >1000){
			Debug_A = 1;									
			}
			
			Debug_x += 0.1;
			Debug_y = Debug_A*sin(Debug_x);
			if(Debug_x > 5000){
			Debug_x = 0;
									
			}			
		}
		
		
//		GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0对应引脚GPIOF.9拉低，亮  等同LED0=0;
//		DebugGetLED_State1 = 64;
////		GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同LED1=1;
//		delay_ms(1);  		   //延时300ms
//		GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0对应引脚GPIOF.0拉高，灭  等同LED0=1;
//		DebugGetLED_State1 = 8;
////		GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同LED1=0;
//		delay_ms(1);                     //延时300ms
			
//		if (DebugSwitch == 0 && DebugSwitchChangeFlag == 1) {
//			DebugSwitchChangeFlag = 0;
//			GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同LED1=1;
//			//printf("%C\r\n",'B');

//		}				
//		else if (DebugSwitch == 1 && DebugSwitchChangeFlag == 0) {
//			DebugSwitchChangeFlag = 1;
//			GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同LED1=0;

//		}
	}
}


/**
*******************下面注释掉的代码是通过 位带 操作实现IO口控制**************************************
	
int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
  while(1)
	{
     LED0=0;			  //LED0亮
	   LED1=1;				//LED1灭
		 delay_ms(500);
		 LED0=1;				//LED0灭
		 LED1=0;				//LED1亮
		 delay_ms(500);
	 }
}
**************************************************************************************************
 **/	
	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOF->BSRRH=GPIO_Pin_9;//LED0亮
	   GPIOF->BSRRL=GPIO_Pin_10;//LED1灭
		 delay_ms(500);
     GPIOF->BSRRL=GPIO_Pin_9;//LED0灭
	   GPIOF->BSRRH=GPIO_Pin_10;//LED1亮
		 delay_ms(500);

	 }
 }	 
**************************************************************************************************
**/	
 



