#ifndef LZ_CLASSIS
#define LZ_CLASSIS
#include "sys.h"
#include "stm32f4xx.h" 
#include "delay.h"
#define Usartx  USART1                          //发送数据串口

#define SPEED_SETTING_RESPONSE_WAITTIME 10
typedef struct
{
	u8 header0;
	u8 header1;
	u8 DataLength;
	u8 CMD_ID;
	u8 data [20];
	u8 xor_num ;
}PC_TypeDef;

extern PC_TypeDef pc_control;



//异或检查字生成检查程序
void xor_check(PC_TypeDef* pc);
int SetLZ_Classis();
int Motor_Send_Data_Pack(int16_t vel,int16_t yaw,int16_t ang);
void Usart_Send_Data(USART_TypeDef* USARTx, u8 *buf, u8 len);
void Set_Motor_Speed(int16_t vel,int16_t yaw,int16_t ang);


////主程序中 使用 异或检查字生成检查程序
//int16_t vel =500,yaw=200,ang=400;
//pc_control.header0 = 0x0A;
//pc_control.header1 = 0x0C;
//pc_control.DataLength = 6;
//pc_control.CMD_ID = 0x01;
////速度数据
//pc_control.data[0] = vel & 0xFF;
//pc_control.data[1] = (vel >> 8) & 0xFF;
////偏航角数据
//pc_control.data[2] = yaw & 0xFF ;
//pc_control.data[3] = (yaw >> 8) & 0xFF;
////原地转向数据
//pc_control.data[4] = ang & 0xFF ;
//pc_control.data[5] = (ang >> 8) & 0xFF;
////初始化异或校验值为0
//pc_control.xor_num = 0;

////调用计算程序计算异或校验值， 并赋值到串口数据结构体的xor_num变量中
//xor_check(&pc_control) ;



////底盘电机与舵机 运动使能
//0A 0C 01 01 01 01
////底盘电机与舵机 运动失能
//0A 0C 01 01 00 00

////下发 前行 0.5m/s ，左转 5 度
//0A 0C 06 02 F4 01 F4 01 00 00 04

////下发 原地左转 0.3 m/s 
//0A 0C 06 02 00 00 00 00 2C 01 29

////下发 零速度指令（底盘将停止，轮子朝向直行位置）
//0A 0C 06 02 00 00 00 00 00 00 04


#endif



