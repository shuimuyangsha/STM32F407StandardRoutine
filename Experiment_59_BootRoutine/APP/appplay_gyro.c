#include "appplay_gyro.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//APP-�����ǲ��� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   

//��Բ��ָ�����
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶�
void gyro_circle_panel(u16 x,u16 y,u16 size,u16 d)
{
	u16 r=size/2;//�õ��뾶 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1; 
	u16 i; 
	gui_fill_circle(x,y,r,WHITE);		//����Ȧ
	gui_fill_circle(x,y,r-4,BLACK);		//����Ȧ
	for(i=0;i<60;i++)//��6���
	{ 
		px0=sx+r+(r-4)*sin((app_pi/30)*i); 
		py0=sy+r-(r-4)*cos((app_pi/30)*i); 
		px1=sx+r+(r-d)*sin((app_pi/30)*i); 
		py1=sy+r-(r-d)*cos((app_pi/30)*i);  
		gui_draw_bline1(px0,py0,px1,py1,0,WHITE);		
	}
	for(i=0;i<12;i++)//��30���
	{ 
		px0=sx+r+(r-5)*sin((app_pi/6)*i); 
		py0=sy+r-(r-5)*cos((app_pi/6)*i); 
		px1=sx+r+(r-d)*sin((app_pi/6)*i); 
		py1=sy+r-(r-d)*cos((app_pi/6)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);		
	}
	for(i=0;i<4;i++)//��90���
	{ 
		px0=sx+r+(r-5)*sin((app_pi/2)*i); 
		py0=sy+r-(r-5)*cos((app_pi/2)*i); 
		px1=sx+r+(r-d-3)*sin((app_pi/2)*i); 
		py1=sy+r-(r-d-3)*cos((app_pi/2)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);		
	}
} 
//��ʾָ��
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶� 
//arg:�Ƕ� -1800~1800,��λ:0.1��
//color:��ɫֵ
void gyro_circle_show(u16 x,u16 y,u16 size,u16 d,s16 arg,u16 color)
{
	u16 r=size/2;//�õ��뾶  
	u16 px1,py1;   
	px1=x+(r-2*d-5)*sin((app_pi/1800)*arg); 
	py1=y-(r-2*d-5)*cos((app_pi/1800)*arg); 
	gui_draw_bline1(x,y,px1,py1,1,color); 
	gui_fill_circle(x+1,y+1,d,color);		//������Ȧ
}
//��ʾ������
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶� 
//parg:������ -900~900,��λ:0.1��
//color:��ɫֵ
void gyro_circle_pitch(u16 x,u16 y,u16 size,u16 d,s16 parg)
{
	static s16 oldpitch=0; 
	u8 *buf;
	float temp;
	if(oldpitch!=parg)
	{
		buf=gui_memin_malloc(100);
		gyro_circle_show(x,y,size,d,oldpitch,BLACK);//�����ԭ������ʾ	
		temp=(float)parg/10;
		sprintf((char*)buf,"%.1f��",temp);//�ٷֱ�  
		gui_fill_rectangle(x-21+6,y+(size/4)-6,42,12,BLACK);//����ɫ 
		gui_show_strmid(x-21+6,y+(size/4)-6,42,12,GREEN,12,buf);//��ʾ�Ƕ�
		gyro_circle_show(x,y,size,d,parg,GREEN);//ָ���µ�ֵ
		oldpitch=parg;	
		gui_memin_free(buf);
	}
}
//��ʾ�����
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶� 
//parg:����� -1800~1800,��λ:0.1��
//color:��ɫֵ
void gyro_circle_roll(u16 x,u16 y,u16 size,u16 d,s16 rarg)
{
	static s16 oldroll=0; 
	u8 *buf;
	float temp;
	if(oldroll!=rarg)
	{
		buf=gui_memin_malloc(100);
		gyro_circle_show(x,y,size,d,oldroll,BLACK);//�����ԭ������ʾ
		temp=(float)rarg/10;
		sprintf((char*)buf,"%.1f��",temp);//�ٷֱ�  
		gui_fill_rectangle(x-24+6,y+(size/4)-6,48,12,BLACK);//����ɫ 
		gui_show_strmid(x-24+6,y+(size/4)-6,48,12,RED,12,buf);//��ʾ�Ƕ�
		gyro_circle_show(x,y,size,d,rarg,RED);//ָ���µ�ֵ
		oldroll=rarg;	
		gui_memin_free(buf);
	}
}
//��ʾ�����
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶� 
//parg:����� -1800~1800,��λ:0.1��
//color:��ɫֵ
void gyro_circle_yaw(u16 x,u16 y,u16 size,u16 d,s16 yarg)
{
	static s16 oldyaw=0; 
	u8 *buf;
	float temp;
	if(oldyaw!=yarg)
	{
		buf=gui_memin_malloc(100);
		gyro_circle_show(x,y,size,d,oldyaw,BLACK);//�����ԭ������ʾ
		temp=(float)yarg/10;
		sprintf((char*)buf,"%.1f��",temp);//�ٷֱ�  
		gui_fill_rectangle(x-24+6,y+(size/4)-6,48,12,BLACK);	//����ɫ 
		gui_show_strmid(x-24+6,y+(size/4)-6,48,12,YELLOW,12,buf);//��ʾ�Ƕ�
		gyro_circle_show(x,y,size,d,yarg,YELLOW);//ָ���µ�ֵ
		oldyaw=yarg;
		gui_memin_free(buf);
	}
}
//DMP��ʾ
u8*const gyro_remind_tbl[2][GUI_LANGUAGE_NUM]=
{
{"��ʼ��DMP,���Ժ�...","��ʼ��DMP,Ո����...","DMP Init,Please wait...",},	 
{"��ʼ������,����...","��ʼ���e�`,Ո�z��...","Init Error,Please check...",},  
};
//DMP��Ϣ
u8*const gyro_msg_tbl[3][GUI_LANGUAGE_NUM]=
{
{"������","������","PITCH",},	 
{"�����","�M�L��","ROLL",}, 
{"�����","�����","YAW",},  
};

//6����������ʾ
u8 appplay_gyro(u8* caption)
{ 
	float pitch,roll,yaw; 
	short temp;
	u8 rval=0;	
	u8 rpr,ry;
	u8 dpr,dy;
	u16 xp;
	u16 ypr;
	u8 fsize; 
 	//��ʾ��ʼ���MPU6050 ��DMP
 	window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)gyro_remind_tbl[0][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
	if(mpu_dmp_init())//��ʼ��DMP
	{
		window_msg_box((lcddev.width-200)/2,(lcddev.height-80)/2,200,80,(u8*)gyro_remind_tbl[1][gui_phy.language],(u8*)APP_REMIND_CAPTION_TBL[gui_phy.language],12,0,0,0);
		delay_ms(500);  
		rval=1;
	}else//��ʼ��OK
	{
		LCD_Clear(BLACK);
		app_gui_tcbar(0,0,lcddev.width,gui_phy.tbheight,0x02);			//�·ֽ���	 
		gui_show_strmid(0,0,lcddev.width,gui_phy.tbheight,WHITE,gui_phy.tbfsize,(u8*)caption);//��ʾ����  
	
		if(lcddev.width==240)
		{
			rpr=59;ry=80;
			dpr=7;dy=8;
			xp=60;ypr=60+gui_phy.tbheight;
			fsize=12;
		}else if(lcddev.width==320)
		{
			rpr=79;ry=140;
			dpr=8;dy=9;
			xp=80;ypr=80+gui_phy.tbheight;
			fsize=12;
		}else if(lcddev.width==480)
		{
			rpr=110;ry=200;
			dpr=10;dy=12;
			xp=120;ypr=120+gui_phy.tbheight;
			fsize=16;
		} 
		gyro_circle_panel(xp,ypr,2*rpr,dpr);					//�������Ǳ���
		gui_show_strmid(xp-(3*fsize)/2,ypr+xp,3*fsize,fsize,GREEN,fsize,(u8*)gyro_msg_tbl[0][gui_phy.language]);//��ʾ����
		gyro_circle_panel(xp+lcddev.width/2,ypr,2*rpr,dpr);		//������Ǳ���
		gui_show_strmid(lcddev.width/2+xp-(3*fsize)/2,ypr+xp,3*fsize,fsize,RED,fsize,(u8*)gyro_msg_tbl[1][gui_phy.language]);//��ʾ����
		gyro_circle_panel(lcddev.width/2,xp*2+gui_phy.tbheight+ry,2*ry,dy);	//������Ǳ���
		if(lcddev.width==480)gui_show_strmid(lcddev.width/2-(3*fsize)/2,xp*2+gui_phy.tbheight+ry*2+10,3*fsize,fsize,YELLOW,fsize,(u8*)gyro_msg_tbl[2][gui_phy.language]);//��ʾ����  
		else gui_show_strmid(lcddev.width/2-(3*fsize)/2,xp*2+gui_phy.tbheight+ry*2+2,3*fsize,fsize,YELLOW,fsize,(u8*)gyro_msg_tbl[2][gui_phy.language]);//��ʾ����  
 		gyro_circle_pitch(xp,ypr,2*rpr,dpr,360);				//��ָ����ʾ����
		gyro_circle_roll(xp+lcddev.width/2,ypr,2*rpr,dpr,360);	//��ָ����ʾ����
		gyro_circle_yaw(lcddev.width/2,xp*2+gui_phy.tbheight+ry,2*ry,dy,360);	//��ָ����ʾ����
		while(1)
		{
			if(system_task_return)break;//TPAD����
			if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡDMP����
			{  
				temp=pitch*10;
				gyro_circle_pitch(xp,ypr,2*rpr,dpr,temp);
				temp=roll*10;
				gyro_circle_roll(xp+lcddev.width/2,ypr,2*rpr,dpr,temp);
				temp=yaw*10;
				gyro_circle_yaw(lcddev.width/2,xp*2+gui_phy.tbheight+ry,2*ry,dy,temp);
 			}
			delay_ms(10);  
		}
	}
	return rval;
}




















