#ifndef __USART6_H
#define __USART6_H
#include "sys.h"
#include "MilWaveRadar.h"



#define USART6_DATA_LENGTH           300                                          //接收数据长度
#define USART6_DATA_FRAME_TYPES      5                                          //缓存区存储数据数量
#define EN_USART6_RX 				         1		                                       //使能（1）/禁止（0）串口1接收

extern char usart6_Recv_Buf[USART6_DATA_FRAME_TYPES*(USART6_DATA_LENGTH+1)] ;    //40*11
extern char Usart6_New_Data_sing ;                                               //串口接收新数据标志


void Usart6_Init(u32 bound);
char* Get_Usart6_Recv_Data_Pointer(int i ,char* p);                              //查询缓存区数据指针
int Set_Usart6_Data_Flag(int i,char* p);

#endif
