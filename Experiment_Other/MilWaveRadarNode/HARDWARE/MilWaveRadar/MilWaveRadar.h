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

	02 01 04 03 06 05 08 07   （同步头）
	04 00 00 02     （版本号）
	A0 00 00 00     （总包长度）
	42 16 0A 00     （平台号）
	96 0D 00 00     （帧序号）

	B5 C1 46 3C     （CPU 时间，时间戳）
	08 00 00 00     （目标数量，样本点数）
	01 00 00 00     （输出结构数目，1个结构）
	00 00 00 00     （子帧序号，没有子帧为0）

	01 00 00 00     （结构体类型）
	64 00 00 00     （结构体长度，从目标数到 0F 0F 0F... 之前）
	08 00           （目标数，检测的目标数）
	09 00           （Q 值，输出格式）

	32 00 00 00 AC 03 23 00 5C 04 00 00 （第1个目标数据）
	33 00 00 00 E2 06 00 00 73 04 00 00 （第2个目标数据）
	34 00 00 00 F4 04 DC FF 89 04 00 00 （第3个目标数据）
	66 00 00 00 22 01 00 00 E6 08 00 00 （第4个目标数据）
	C7 00 00 00 34 00 47 10 0B 06 00 00 （第5个目标数据）
	C8 00 00 00 2E 00 D1 0F 61 07 00 00 （第6个目标数据）
	FA 00 00 00 0C 00 69 F4 7B 12 00 00 （第7个目标数据）
	FA 00 00 00 0A 00 C5 13 39 09 00 00 （第8个目标数据）

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













