#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	
#include "../StandbyGPIO/StandbyGPIO.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//RS485���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
	  	
extern u8 RS485_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern u8 RS485_RX_CNT;   			//���յ������ݳ���

//ģʽ����
#define RS485_TX_EN		PGout(8)	//485ģʽ����.0,����;1,����.
//����봮���жϽ��գ�����EN_USART2_RXΪ1����������Ϊ0
#define EN_USART2_RX 	1			//0,������;1,����.

#define FRAME_RX_BUFFER_LENGTH   9


typedef struct frame_statistical_struct {
	u16 frame_total;				//ͳ��֡��������֡��ŵ����ֵ
	u16 previous_frame_serial_number;		//֡���
	u16 current_frame_serial_number;		//��ǰ֡���
	int receive_frame_count;		//�ɹ�����֡����
	float receive_success_rate		//���ճɹ���
	
} FrameStatisticalStruct;



extern FrameStatisticalStruct frame_statistical;
														 
void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf,u8 *len);		

void Processing_statistical_results(FrameStatisticalStruct *pframe_statistical);
#endif	   
















