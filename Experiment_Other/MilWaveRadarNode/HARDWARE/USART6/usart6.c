#include "usart6.h"

#if SYSTEM_SUPPORT_OS
#include "includes.h"
#endif

#define USART6_RECV_FRAME_DONE_FLAG  0x8000                                  //接收完成标志


char usart6_Recv_Buf[USART6_DATA_FRAME_TYPES*(USART6_DATA_LENGTH+1)] = {0};  //40*11
char Usart6_New_Data_sing = 0;                                               //串口接收新数据标志
uint16_t Usart6_Recv_Status = 0;                                             //串口接收数据标志
char recn_buf[500] = {0};                                                     //临时存储接收到的数据

/************************************************************************
函数名称: void Usart6_Init(u32 bound)
函数功能: usart6初始化函数
输入参数: 
返 回 值: 
************************************************************************/
void Usart6_Init(u32 bound)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	USART_DeInit(USART6);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6); //
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); //

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_Cmd(USART6, ENABLE);

#if EN_USART6_RX	
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//ICP	工控机
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}

/**********************************************************************
函数名称:char* Get_Usart6_Recv_Pointer(char* p)
函数功能:获取数据真位置存储数据
输入参数:
返 回 值: 数据指针
***********************************************************************/
char* Get_Usart6_Recv_Pointer(char* p)
{
	int i;

	for(i=0;i<USART6_DATA_FRAME_TYPES;i++)
	{
		if(0 == *(p+i*(USART6_DATA_LENGTH +1)))
		{
			*(p+i*(USART6_DATA_LENGTH +1)) = 1;   //标记数据有效
			return (p+i*(USART6_DATA_LENGTH +1));
		}
	}
	i= 0;
			*(p+i*(USART6_DATA_LENGTH +1)) = 1;   //标记数据有效
			return (p+i*(USART6_DATA_LENGTH +1));
}
/**********************************************************************
函数名称: char* Get_Usart6_Recv_Pointer(char* p)
函数功能: 查询数据指针
输入参数:
返 回 值: 数据指针
***********************************************************************/
char* Get_Usart6_Recv_Data_Pointer(int i ,char* p)
{
	return (p+i*(USART6_DATA_LENGTH +1)+1);
}
/**********************************************************************
函数名称:char* Get_Usart6_Recv_Pointer(char* p)
函数功能:查询数据有无
输入参数:
返 回 值: 
***********************************************************************/
int Set_Usart6_Data_Flag(int i,char* p)
{
	if(1 == *(p+i*(USART6_DATA_LENGTH +1)))
	{
		*(p+i*(USART6_DATA_LENGTH +1)) = 0;//标记数据取走
		return 1;
	}
	else
	{
		return 0;
	}
}
/**********************************************************************
函数名称: void USART6_IRQHandler(void)
函数功能: usart6中断服务函数
输入参数:
返 回 值: 
***********************************************************************/
void USART6_IRQHandler(void)
{
	u8 res;
	u8 i;
	u8 sum;
  char *pFrame;
#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();
#endif
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART6);


		if (Usart6_Recv_Status < 500) {
		
			recn_buf[Usart6_Recv_Status] = res;
			Usart6_Recv_Status++;
		}
		else {
			Usart6_Recv_Status = 0;
		}

		if (Usart6_Recv_Status == 3) {
			if (recn_buf[0] != 0x02 ||
				recn_buf[1] != 0x01 ||
				recn_buf[2] != 0x04
				//recn_buf[3] != 0x03 ||
				//recn_buf[4] != 0x06 ||
				//recn_buf[5] != 0x05 ||
				//recn_buf[6] != 0x07 ||
				//recn_buf[7] != 0x08
				) {

				Usart6_Recv_Status = 0;
			}
		}
		if (Usart6_Recv_Status == 15) {

			radar.tatalpacketlen = recn_buf[12];
		}

		if (Usart6_Recv_Status > 15 &&
			radar.tatalpacketlen == Usart6_Recv_Status) {
			radar.version = recn_buf[8] | recn_buf[9] << 8 | recn_buf[10] << 16 | recn_buf[11] << 24;
			radar.frameNumber = recn_buf[20] | recn_buf[21] << 8 | recn_buf[22] << 16 | recn_buf[23] << 24;


			radar.timecpucycles = recn_buf[24] | recn_buf[25] << 8 | recn_buf[26] << 16 | recn_buf[27]<<24;

			radar.numdetedobj = recn_buf[48] | (recn_buf[49] << 8);
			radar.xyzoutputoformat = recn_buf[50] | (recn_buf[51] << 8);


			radar.object.rIdx = recn_buf[12];

/*******************雷达对象点数据转存*******************/
			//for (i = 0; i < radar.numdetedobj; i++) {
			//	radar_object[i * 12 + 0].rIdx = recn_buf[52 + i * 12 + 0] | (recn_buf[52 + i * 12 + 1] << 8);
			//	radar_object[i * 12 + 1].dIdx = recn_buf[52 + i * 12 + 2] | (recn_buf[52 + i * 12 + 3] << 8);
			//	radar_object[i * 12 + 2].peakVal = recn_buf[52 + i * 12 + 4] | (recn_buf[52 + i * 12 + 5] << 8);

			//	radar_object[i * 12 + 3].x = recn_buf[52 + i * 12 + 6] | (recn_buf[52 + i * 12 + 7] << 8);
			//	radar_object[i * 12 + 4].y = recn_buf[52 + i * 12 + 8] | (recn_buf[52 + i * 12 + 9] << 8);
			//	radar_object[i * 12 + 5].z = recn_buf[52 + i * 12 + 10] | (recn_buf[52 + i * 12 + 11] << 8);
			//
			//}

			//radarX0, radarX1, radarX2, radarX3, radarX4, radarX5;
			//radarY0, radarY1, radarY2, radarY3, radarY4, radarY5;
			radarX0 = recn_buf[52 + 0 * 12 + 6] | (recn_buf[52 + 0 * 12 + 7] << 8);
			radarY0 = recn_buf[52 + 0 * 12 + 8] | (recn_buf[52 + 0 * 12 + 9] << 8);
/*******************雷达对象点数据转存*******************/



			
			Usart6_Recv_Status = 0;
		}












		//if ((Usart6_Recv_Status == 0 && res != 0x02) || (Usart6_Recv_Status == 1 && res != 0x01)
		//	|| (Usart6_Recv_Status == (USART6_DATA_LENGTH-2) && res != 0xFF)
		//	|| (Usart6_Recv_Status == (USART6_DATA_LENGTH-1) && res != 0xFE))
		//{
		//	Usart6_Recv_Status = 0;
		//	if (res == 0x02)
		//	{
		//		recn_buf[Usart6_Recv_Status] = res;
		//		++Usart6_Recv_Status;
		//	}
		//	goto end;
		//}


		//if (Usart6_Recv_Status == (USART6_DATA_LENGTH-3))
		//{
		//	sum = 0;
		//	for (i = 2; i < (USART6_DATA_LENGTH-3); ++i)
		//	{
		//		sum += recn_buf[i];
		//	}
		//	if (res != sum)
		//	{
		//		Usart6_Recv_Status = 0;
		//		if (res == 0x55)
		//		{
		//			recn_buf[Usart6_Recv_Status] = res;
		//			++Usart6_Recv_Status;
		//		}
		//		goto end;
		//	}
		//}
		//if ((Usart6_Recv_Status & USART6_RECV_FRAME_DONE_FLAG) == 0)
		//{
		//	if (Usart6_Recv_Status < USART6_DATA_LENGTH)
		//	{
		//		recn_buf[Usart6_Recv_Status] = res;
		//		++Usart6_Recv_Status;
		//		if (Usart6_Recv_Status == USART6_DATA_LENGTH)
		//		{
		//			Usart6_Recv_Status |= USART6_RECV_FRAME_DONE_FLAG; // indicate one frame received
		//			pFrame = Get_Usart6_Recv_Pointer(usart6_Recv_Buf);  //查找存储数据位置
		//			memcpy((void*)(pFrame + 1), (const void*)(&recn_buf), sizeof(recn_buf));//存储数据到接收缓存区
		//			Usart6_New_Data_sing = 1;                                //标记有新的控制指令
		//			Usart6_Recv_Status = 0;
		//		}
		//	}
		//	else 
		//	{
		//		Usart6_Recv_Status = 0;
		//		if (res == 0x55)
		//		{
		//			recn_buf[Usart6_Recv_Status] = res;
		//			++Usart6_Recv_Status;
		//		}
		//	}
		//}
	}
end:;
#if SYSTEM_SUPPORT_OS 	
	OSIntExit();
#endif
}





