#include "../StandbyGPIO/StandbyGPIO.h"

void StandbyIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_AHB1PeriphClockCmd(StandbyIO1_GPIO_CLK, ENABLE);	 		//使能端口时钟
	RCC_AHB1PeriphClockCmd(StandbyIO2_GPIO_CLK, ENABLE);			//使能端口时钟
	RCC_AHB1PeriphClockCmd(StandbyIO3_GPIO_CLK, ENABLE);		 	//使能端口时钟
	RCC_AHB1PeriphClockCmd(StandbyIO4_GPIO_CLK, ENABLE);	 		//使能端口时钟
	RCC_AHB1PeriphClockCmd(StandbyIO5_GPIO_CLK, ENABLE);			//使能端口时钟
	RCC_AHB1PeriphClockCmd(StandbyIO6_GPIO_CLK, ENABLE);		 	//使能端口时钟
	
	GPIO_InitStructure.GPIO_Pin = StandbyIO1_PIN ;				 	//StandbyIO1 端口配置	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(StandbyIO1_GPIO_PORT, &GPIO_InitStructure);			
	
	GPIO_InitStructure.GPIO_Pin = StandbyIO2_PIN ;				 	//StandbyIO2 端口配置	
	GPIO_Init(StandbyIO2_GPIO_PORT, &GPIO_InitStructure);				

	GPIO_InitStructure.GPIO_Pin = StandbyIO3_PIN ;				 	//StandbyIO3 端口配置	
	GPIO_Init(StandbyIO3_GPIO_PORT, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = StandbyIO4_PIN ;				 	//StandbyIO3 端口配置	
	GPIO_Init(StandbyIO4_GPIO_PORT, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin = StandbyIO5_PIN ;				 	//StandbyIO3 端口配置	
	GPIO_Init(StandbyIO5_GPIO_PORT, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = StandbyIO6_PIN ;				 	//StandbyIO3 端口配置	
	GPIO_Init(StandbyIO6_GPIO_PORT, &GPIO_InitStructure);

	StandbyIO1(StandbyIO_OFF);	
	StandbyIO2(StandbyIO_OFF);
	StandbyIO3(StandbyIO_OFF);
	StandbyIO4(StandbyIO_OFF);	
	StandbyIO5(StandbyIO_OFF);
	StandbyIO6(StandbyIO_OFF);	
}

