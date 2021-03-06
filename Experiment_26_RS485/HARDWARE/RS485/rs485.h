#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	
#include "../StandbyGPIO/StandbyGPIO.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//RS485驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
	  	
extern u8 RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 RS485_RX_CNT;   			//接收到的数据长度

//模式控制
#define RS485_TX_EN		PGout(8)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，设置EN_USART2_RX为1，否则设置为0
#define EN_USART2_RX 	1			//0,不接收;1,接收.

#define FRAME_RX_BUFFER_LENGTH   9

//#pragma pack (1)
typedef struct frame_statistical_struct {
	u16 frame_total;				//统计帧总数，即帧编号的最大值
	u16 previous_frame_serial_number;		//帧编号
	u16 current_frame_serial_number;		//当前帧编号
	int receive_frame_count;		//成功接收帧计数
	float receive_success_rate		//接收成功率
	
} FrameStatisticalStruct;
//#pragma pack ()


extern FrameStatisticalStruct frame_statistical;
														 
void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf,u8 *len);		

void Processing_statistical_results(FrameStatisticalStruct *pframe_statistical);
#endif	   
















