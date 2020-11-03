#include "LZ_Classis.h"


PC_TypeDef pc_control;

u8 Usart_Send_Data_Buf[20] = {0};                        //发送数据数组

/**********************************************************************
函数名称 : void Motor_PowerOn(void)
函数功能 : 电机上电函数
输入参数 : 
返 回 值 :  无
***********************************************************************/
void Motor_Power_On(void)
{
  	pc_control.header0 = 0x0A;
	pc_control.header1 = 0x0C;
	pc_control.DataLength = 01;
	pc_control.CMD_ID = 0x01;
	//速度数据
	pc_control.data[0] = 0x01 & 0xFF;

	//初始化异或校验值为0
	pc_control.xor_num = 0;

	//调用计算程序计算异或校验值， 并赋值到串口数据结构体的xor_num变量中
	xor_check(&pc_control) ;
	
	Usart_Send_Data_Buf[0] = pc_control.header0;
	Usart_Send_Data_Buf[1] = pc_control.header1;
	Usart_Send_Data_Buf[2] = pc_control.DataLength;
	Usart_Send_Data_Buf[3] = pc_control.CMD_ID;	
	Usart_Send_Data_Buf[4] = pc_control.data[0];		
	Usart_Send_Data_Buf[5] = pc_control.xor_num;		
	
	
	Usart_Send_Data(Usartx,Usart_Send_Data_Buf, 6);                                    //左轮数据发送
    delay_ms(SPEED_SETTING_RESPONSE_WAITTIME);                                         //发送时间间隔
}

/**********************************************************************
函数名称 : void Set_Motor_Speed(int left_speed,int right_speed)
函数功能 : 设置电机速度  单位 mm/s       下发速度单位为  0.1RPM
输入参数 : 
返 回 值 :  无
***********************************************************************/
float DebugUCProbe_Set_Motor_Speed_left_speed;
float DebugUCProbe_Set_Motor_Speed_right_speed;
void Set_Motor_Speed(int16_t vel,int16_t yaw,int16_t ang)
{	
//  float LEFT_RPM = 0;      //电机转速  rpm
//  float RIGHT_RPM = 0;     //电机转速  rpm
//  int SET_LEFT_RPM = 0;    //电机转速  rpm  实际下发
//  int SET_RIGHT_RPM = 0;   //电机转速  rpm  实际下发
//	static u8 left_clock_sing = 0;
//	static u8 right_clock_sing = 0;

//	
//	LEFT_RPM = (float)(-1) * ((left_speed *60.0f)/TYRE_PERIMETER)*REDUCTION_RATIO;
//	RIGHT_RPM= (float)       ((right_speed *60.0f)/TYRE_PERIMETER)*REDUCTION_RATIO;	
//	SET_LEFT_RPM = (int)(LEFT_RPM * 10.0f);
//	SET_RIGHT_RPM = (int)(RIGHT_RPM* 10.0f);
//	DebugUCProbe_Set_Motor_Speed_left_speed = SET_LEFT_RPM;
//	DebugUCProbe_Set_Motor_Speed_right_speed = SET_RIGHT_RPM;

  Motor_Send_Data_Pack(vel,yaw,ang);
	Usart_Send_Data(Usartx,Usart_Send_Data_Buf, 11);                                    //左轮数据发送
	delay_ms(SPEED_SETTING_RESPONSE_WAITTIME);                                                                       //发送时间间隔

}

/**********************************************************************
函数名称 : void Motor_PowerOff(void)
函数功能 : 电机松轴函数
输入参数 : 
返 回 值 :  无
***********************************************************************/
//void Motor_Power_Off(void)
//{
//  Motor_Send_Data_Pack(Rs485_Send_Data_Buf,LEFT_MOTOT_ID,WOITE_SINGLE_REGISTER,MOTOR_ENABLE,MOTOR_DISABLE_DATA);   //左轮数据打包
//	Rs485_Usart_Send_Data(Usartx,Rs485_Send_Data_Buf, XIAOZHUO_TX_BUFFER_LENGTH);                                    //左轮数据发送
//	delay_ms(SPEED_SETTING_RESPONSE_WAITTIME);                                                                       //发送时间间隔

//  Motor_Send_Data_Pack(Rs485_Send_Data_Buf,RIGHT_MOTOR_ID,WOITE_SINGLE_REGISTER,MOTOR_ENABLE,MOTOR_DISABLE_DATA);  //右轮数据打包
//	Rs485_Usart_Send_Data(Usartx,Rs485_Send_Data_Buf, XIAOZHUO_TX_BUFFER_LENGTH);                                    //左轮数据发送
//	delay_ms(SPEED_SETTING_RESPONSE_WAITTIME);                                                                       //发送时间间隔
//}


/**********************************************************************
函数名称 : void Motor_Init(void)
函数功能 : 电机初始化
输入参数 : 
返 回 值 :  无
***********************************************************************/
void Motor_Init(void)                               //轮机初始化
{
	Motor_Power_On();//电机上电
//  Set_Motor_Max_Speed(MAX_MOTOR_SPEED);
	Set_Motor_Speed(800,1200,0);
	//DisableParkBark();
	//EnableParkBark();
}




//异或检查字生成检查程序
void xor_check(PC_TypeDef* pc)
{
	u8 temp = 0;
	u8 i=0;

	temp ^= pc->CMD_ID;
	temp ^= pc->DataLength;

	for(i=0;i< pc->DataLength;i++)
	{
		temp ^= pc->data[i];
	}
	pc->xor_num = temp;
}


int Motor_Send_Data_Pack(int16_t vel,int16_t yaw,int16_t ang)
{
	//主程序中 使用 异或检查字生成检查程序
//	int16_t vel =500,yaw=200,ang=400;
	pc_control.header0 = 0x0A;
	pc_control.header1 = 0x0C;
	pc_control.DataLength = 6;
	pc_control.CMD_ID = 0x02;
	//速度数据
	pc_control.data[0] = vel & 0xFF;
	pc_control.data[1] = (vel >> 8) & 0xFF;
	//偏航角数据
	pc_control.data[2] = yaw & 0xFF ;
	pc_control.data[3] = (yaw >> 8) & 0xFF;
	//原地转向数据
	pc_control.data[4] = ang & 0xFF ;
	pc_control.data[5] = (ang >> 8) & 0xFF;
	//初始化异或校验值为0
	pc_control.xor_num = 0;

	//调用计算程序计算异或校验值， 并赋值到串口数据结构体的xor_num变量中
	xor_check(&pc_control) ;
	

	Usart_Send_Data_Buf[0] = pc_control.header0;
	Usart_Send_Data_Buf[1] = pc_control.header1;
	Usart_Send_Data_Buf[2] = pc_control.DataLength;
	Usart_Send_Data_Buf[3] = pc_control.CMD_ID;	
	Usart_Send_Data_Buf[4] = pc_control.data[0];
	Usart_Send_Data_Buf[5] = pc_control.data[1];
	Usart_Send_Data_Buf[6] = pc_control.data[2];
	Usart_Send_Data_Buf[7] = pc_control.data[3];
	Usart_Send_Data_Buf[8] = pc_control.data[4];
	Usart_Send_Data_Buf[9] = pc_control.data[5];	
	Usart_Send_Data_Buf[10] = pc_control.xor_num;		
	
	
	
}



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



/**************************************************************************************************************************************
函数名称: Usart_Send_Data(USART_TypeDef* USARTx, u8 *buf, u8 len)
函数功能: 使用485串口发送数据
输入参数: 
返 回 值: 数据指针
*************************************************************************************************************************************/
void Usart_Send_Data(USART_TypeDef* USARTx, u8 *buf, u8 len)
{
	u8 t;

	for (t = 0; t < len; t++)		//循环发送数据
	{
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //等待发送结束		
		USART_SendData(USARTx, buf[t]); //发送数据
	}
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //等待发送结束	

}



