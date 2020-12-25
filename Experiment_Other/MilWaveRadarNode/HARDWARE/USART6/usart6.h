#ifndef __USART6_H
#define __USART6_H
#include "sys.h"
#include "MilWaveRadar.h"



#define USART6_DATA_LENGTH           300                                          //�������ݳ���
#define USART6_DATA_FRAME_TYPES      5                                          //�������洢��������
#define EN_USART6_RX 				         1		                                       //ʹ�ܣ�1��/��ֹ��0������1����

extern char usart6_Recv_Buf[USART6_DATA_FRAME_TYPES*(USART6_DATA_LENGTH+1)] ;    //40*11
extern char Usart6_New_Data_sing ;                                               //���ڽ��������ݱ�־


void Usart6_Init(u32 bound);
char* Get_Usart6_Recv_Data_Pointer(int i ,char* p);                              //��ѯ����������ָ��
int Set_Usart6_Data_Flag(int i,char* p);

#endif
