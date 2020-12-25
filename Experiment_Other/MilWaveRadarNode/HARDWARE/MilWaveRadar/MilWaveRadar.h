#ifndef __MILWAVERADAR_H
#define __MILWAVERADAR_H

#include "sys.h"

#define  TOTAL_POINT 20

typedef struct radar_object_struct {
	u16	rIdx;
	u16	dIdx;
	u16	peakVal;
	u16	x;
	u16	y;
	u16	z;



}RadarObjectStruct;



typedef struct radar_struct {

	/*
	head
	version
	tatalpacketlen
	platform
	frameNumber
	timecpucycles
	numdetectobj
	numTLVs
	subFrameNumber
	type
	length

	numdetedobj
	xyzoutputoformat

	rIdx
	dIdx
	peakVal
	x
	y
	z

	02 01 04 03 06 05 08 07   ��ͬ��ͷ��
	04 00 00 02     ���汾�ţ�
	A0 00 00 00     ���ܰ����ȣ�
	42 16 0A 00     ��ƽ̨�ţ�
	96 0D 00 00     ��֡��ţ�

	B5 C1 46 3C     ��CPU ʱ�䣬ʱ�����
	08 00 00 00     ��Ŀ������������������
	01 00 00 00     ������ṹ��Ŀ��1���ṹ��
	00 00 00 00     ����֡��ţ�û����֡Ϊ0��

	01 00 00 00     ���ṹ�����ͣ�
	64 00 00 00     ���ṹ�峤�ȣ���Ŀ������ 0F 0F 0F... ֮ǰ��
	08 00           ��Ŀ����������Ŀ������
	09 00           ��Q ֵ�������ʽ��

	32 00 00 00 AC 03 23 00 5C 04 00 00 ����1��Ŀ�����ݣ�
	33 00 00 00 E2 06 00 00 73 04 00 00 ����2��Ŀ�����ݣ�
	34 00 00 00 F4 04 DC FF 89 04 00 00 ����3��Ŀ�����ݣ�
	66 00 00 00 22 01 00 00 E6 08 00 00 ����4��Ŀ�����ݣ�
	C7 00 00 00 34 00 47 10 0B 06 00 00 ����5��Ŀ�����ݣ�
	C8 00 00 00 2E 00 D1 0F 61 07 00 00 ����6��Ŀ�����ݣ�
	FA 00 00 00 0C 00 69 F4 7B 12 00 00 ����7��Ŀ�����ݣ�
	FA 00 00 00 0A 00 C5 13 39 09 00 00 ����8��Ŀ�����ݣ�

	0F 0F 0F 0F 0F 0F 0F 0F 0F 0F 0F 0F

	*/
	
	//	head
	u32	version;
	u32 tatalpacketlen;
	//	platform
	u32	frameNumber;
	u32	timecpucycles;
	//	numdetectobj
	//	numTLVs
	//	subFrameNumber
	//	type
	//	length

	u16	numdetedobj;
	u16	xyzoutputoformat;

	//	rIdx
	//	dIdx
	//	peakVal
	//	x
	//	y
	//	z

	RadarObjectStruct object;


}RadarStruct;




extern RadarStruct radar;
extern RadarObjectStruct radar_object[30];

extern u16 numpoint ;

extern u16 radarX[TOTAL_POINT];
extern u16 radarY[TOTAL_POINT];

extern u16 radarX0, radarX1, radarX2, radarX3, radarX4, radarX5;
extern u16 radarY0, radarY1, radarY2, radarY3, radarY4, radarY5;



#endif













