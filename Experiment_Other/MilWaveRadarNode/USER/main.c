#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart6.h"
#include "MilWaveRadar.h"
#include "math.h"

extern u16 debugX[8] = {1,2,3,4,5};
extern u16 debugY[8] = {1,2,3,4,5};

u16 debugX2 = 0;
u16 debugY2 = 0;

int main(void)
{ 
	u16 i;
	u8 t;
	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	Usart6_Init(921600);		//���ڳ�ʼ��������Ϊ921600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	while(1)
	{
		debugX[0] = 100;
		debugY[0] = sin(debugX[0]);
		debugX[1] = 200;
		debugY[1] = sin(debugX[1]);
		debugX[2] = 300;
		debugY[2] = sin(debugX[2]);
		//debugX[4] = 400;
		//debugY[4] = 400;
		//debugX[5] = 500;
		//debugY[5] = 500;
		debugX2 = i++;
		debugY2 = debugX2+10;
		//for (i = 0; i < 10;i++) {

		//	debugX[i] = i*10.3;
		//	debugY[i] = (i + 3)*10.3;
		//	delay_ms(2000);
		//}
		delay_ms(100);

		//if(USART_RX_STA&0x8000)
		//{					   
		//	len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
		//	printf("\r\n�����͵���ϢΪ:\r\n");
		//	for(t=0;t<len;t++)
		//	{
		//		USART_SendData(USART1, USART_RX_BUF[t]);         //�򴮿�1��������
		//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		//	}
		//	printf("\r\n\r\n");//���뻻��
		//	USART_RX_STA=0;
		//}else
		//{
		//	times++;
		//	if(times%5000==0)
		//	{
		//		printf("\r\nALIENTEK ̽����STM32F407������ ����ʵ��\r\n");
		//		printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
		//	}
		//	if(times%200==0)printf("����������,�Իس�������\r\n");  
		//	if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
		//	delay_ms(10);   
		//}
	}
}

