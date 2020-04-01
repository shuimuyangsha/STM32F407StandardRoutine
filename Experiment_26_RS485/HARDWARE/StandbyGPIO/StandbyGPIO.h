#ifndef __STANDBY_GPIO_H
#define __STANDBY_GPIO_H
#include "sys.h"

//��������
/*******************************************************/
//Ԥ��GPIO1
#define StandbyIO1_PIN                  		GPIO_Pin_0               
#define StandbyIO1_GPIO_PORT            		GPIOB                      
#define StandbyIO1_GPIO_CLK             		RCC_AHB1Periph_GPIOB

//Ԥ��GPIO2
#define StandbyIO2_PIN                  		GPIO_Pin_1                
#define StandbyIO2_GPIO_PORT           			GPIOB                    
#define StandbyIO2_GPIO_CLK             		RCC_AHB1Periph_GPIOB

//Ԥ��GPIO3
#define StandbyIO3_PIN                  		GPIO_Pin_4               
#define StandbyIO3_GPIO_PORT            		GPIOC                       
#define StandbyIO3_GPIO_CLK             		RCC_AHB1Periph_GPIOC

//Ԥ��GPIO4
#define StandbyIO4_PIN                  		GPIO_Pin_5                
#define StandbyIO4_GPIO_PORT            		GPIOC                       
#define StandbyIO4_GPIO_CLK             		RCC_AHB1Periph_GPIOC

//Ԥ��GPIO5
#define StandbyIO5_PIN                  		GPIO_Pin_3                
#define StandbyIO5_GPIO_PORT            		GPIOG                       
#define StandbyIO5_GPIO_CLK             		RCC_AHB1Periph_GPIOG

//Ԥ��GPIO6
#define StandbyIO6_PIN                  		GPIO_Pin_4                
#define StandbyIO6_GPIO_PORT            		GPIOG                       
#define StandbyIO6_GPIO_CLK             		RCC_AHB1Periph_GPIOG

/************************************************************/

/************ ����StandbyIO���صĺ꣬*****************************/
//Ԥ��GPIO�ߵ�ƽ��ͨ������ON=1��OFF=0
//	
/************************************************************/
#define StandbyIO_ON  1
#define StandbyIO_OFF 0

#define debug 1

//Ԥ��GPIO����ģʽ
#define CloseAll_StandbyIO 					1
#define OpenOnly_StandbyIO1 				2
#define OpenOnly_StandbyIO2 				3
#define OpenOnly_StandbyIO3 				4
#define OpenOnly_StandbyIO4 				5
#define OpenOnly_StandbyIO5 				6
#define OpenOnly_StandbyIO6 				7

#define OpenAll_StandbyIO 					8

/* ���κ꣬��������������һ��ʹ�� */
#define StandbyIO1(a)	if (a)	\
					GPIO_SetBits(StandbyIO1_GPIO_PORT,StandbyIO1_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO1_GPIO_PORT,StandbyIO1_PIN)

#define StandbyIO2(a)	if (a)	\
					GPIO_SetBits(StandbyIO2_GPIO_PORT,StandbyIO2_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO2_GPIO_PORT,StandbyIO2_PIN)

#define StandbyIO3(a)	if (a)	\
					GPIO_SetBits(StandbyIO3_GPIO_PORT,StandbyIO3_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO3_GPIO_PORT,StandbyIO3_PIN)

#define StandbyIO4(a)	if (a)	\
					GPIO_SetBits(StandbyIO4_GPIO_PORT,StandbyIO4_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO4_GPIO_PORT,StandbyIO4_PIN)	

#define StandbyIO5(a)	if (a)	\
					GPIO_SetBits(StandbyIO5_GPIO_PORT,StandbyIO5_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO5_GPIO_PORT,StandbyIO5_PIN)

#define StandbyIO6(a)	if (a)	\
					GPIO_SetBits(StandbyIO6_GPIO_PORT,StandbyIO6_PIN);\
					else		\
					GPIO_ResetBits(StandbyIO6_GPIO_PORT,StandbyIO6_PIN)						

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)					{p->BSRRL=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)					{p->BSRRH=i;}				//����͵�ƽ
#define digitalToggle(p,i)				{p->ODR ^=i;}			//�����ת״̬

//StandbyIO״̬��ת
/*******************************************************/
#define StandbyIO1_TOGGLE		digitalToggle(StandbyIO1_GPIO_PORT,StandbyIO1_PIN)
#define StandbyIO2_TOGGLE		digitalToggle(StandbyIO2_GPIO_PORT,StandbyIO2_PIN)
#define StandbyIO3_TOGGLE		digitalToggle(StandbyIO3_GPIO_PORT,StandbyIO3_PIN)
#define StandbyIO4_TOGGLE		digitalToggle(StandbyIO4_GPIO_PORT,StandbyIO4_PIN)
#define StandbyIO5_TOGGLE		digitalToggle(StandbyIO5_GPIO_PORT,StandbyIO5_PIN)
#define StandbyIO6_TOGGLE		digitalToggle(StandbyIO6_GPIO_PORT,StandbyIO6_PIN)				

void StandbyIO_Init(void);//��ʼ��	

#endif

