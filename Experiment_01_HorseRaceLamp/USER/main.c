#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include  "probe_scope_cfg.h"
#include  "probe_scope.h"
#include "math.h"

//ALIENTEK ̽����STM32F407������ ʵ��1
//�����ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


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
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	ProbeScope_Init(1000000);
	
  /**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ��IO����**/	
	
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
		
		
//		GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0��Ӧ����GPIOF.9���ͣ���  ��ͬLED0=0;
//		DebugGetLED_State1 = 64;
////		GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1��Ӧ����GPIOF.10���ߣ��� ��ͬLED1=1;
//		delay_ms(1);  		   //��ʱ300ms
//		GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0��Ӧ����GPIOF.0���ߣ���  ��ͬLED0=1;
//		DebugGetLED_State1 = 8;
////		GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1��Ӧ����GPIOF.10���ͣ��� ��ͬLED1=0;
//		delay_ms(1);                     //��ʱ300ms
			
//		if (DebugSwitch == 0 && DebugSwitchChangeFlag == 1) {
//			DebugSwitchChangeFlag = 0;
//			GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1��Ӧ����GPIOF.10���ߣ��� ��ͬLED1=1;
//			//printf("%C\r\n",'B');

//		}				
//		else if (DebugSwitch == 1 && DebugSwitchChangeFlag == 0) {
//			DebugSwitchChangeFlag = 1;
//			GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1��Ӧ����GPIOF.10���ͣ��� ��ͬLED1=0;

//		}
	}
}


/**
*******************����ע�͵��Ĵ�����ͨ�� λ�� ����ʵ��IO�ڿ���**************************************
	
int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
  while(1)
	{
     LED0=0;			  //LED0��
	   LED1=1;				//LED1��
		 delay_ms(500);
		 LED0=1;				//LED0��
		 LED1=0;				//LED1��
		 delay_ms(500);
	 }
}
**************************************************************************************************
 **/	
	
/**
*******************����ע�͵��Ĵ�����ͨ�� ֱ�Ӳ����Ĵ��� ��ʽʵ��IO�ڿ���**************************************
int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
     GPIOF->BSRRH=GPIO_Pin_9;//LED0��
	   GPIOF->BSRRL=GPIO_Pin_10;//LED1��
		 delay_ms(500);
     GPIOF->BSRRL=GPIO_Pin_9;//LED0��
	   GPIOF->BSRRH=GPIO_Pin_10;//LED1��
		 delay_ms(500);

	 }
 }	 
**************************************************************************************************
**/	
 



