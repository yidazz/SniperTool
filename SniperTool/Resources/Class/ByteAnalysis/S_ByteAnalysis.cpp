#include "S_ByteAnalysis.h"

/* 使用一个业务发送器资源 */
extern SServiceSender *OSCServiceSender;

/* 使用一个外部字节接收队列缓存区资源 */
//extern SVector *OSCRecByteQueue;

/* 使用一个微秒定时器资源 */
extern STimerUs *OSCSendTimerUs;
/* 使用一个微秒定时器资源 */
extern STimerUs *OSCRecTimerUs;

/* 使用一个消息内存资源 */
extern SDataSpace *DataSpace;
/* 使用一个临时测试用定时器资源 */
STimerUs *Temp1 =new STimerUs;
STimerUs *Temp2 = new STimerUs;
STimerUs *Temp3 = new STimerUs;

uint Sa1 = 0;
uint Sa2 = 0;
int temp = 0;

void TempMakeMsg(MESSAGE* Message)
{
	for (int i = 0;i < 100;i++)
	{
		Message->Data[i] = 3;
	}
	Message->DestNum = OSCSendThreadNum;
}

SFirAnalysis::SFirAnalysis()
{
}

SFirAnalysis::~SFirAnalysis()
{
}

bool SFirAnalysis::FirAnalysis(char &rRecByte)
{
	unsigned int NewMemory;
	char TempData[1] = { 1 };
	/** 收到帧的开头 */
	//if (ProFir_Header == rRecByte)
	//{
	//	/** 判断缓存区中是否有残缺数据 */
	//	if (NULL != OSCRecByteQueue->Queue1.size())
	//	{
	//		/* 有残缺数据 则拷贝到数据队列缓存区 */
	//		OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
	//		/* 清空临时缓存区 */
	//		OSCRecByteQueue->Queue1.clear();
	//		/* 将新数据存入临时缓存区 */
	//		OSCRecByteQueue->Queue1.push_back(rRecByte);
	//		/* 收到错误数据 */
	//		State = FrameError;
	//	}
	//	else
	//	{
	//		/* 将新数据存入临时缓存区 */
	//		OSCRecByteQueue->Queue1.push_back(rRecByte);
	//	}
	//}
	///** 收到帧的结尾 */
	//else if (ProFir_End == rRecByte)
	//{
	//	/* 将新数据存入临时缓存区 */
	//	OSCRecByteQueue->Queue1.push_back(rRecByte);
	//	/* 判断帧是否满足条件 */
	//	if(TRUE!= FirConfirm())
	//	{
	//		/* 收到错误数据 */
	//		State = FrameError;
	//	}
	//	else
	//	{
	//		/* 收到完整数据 */
	//		State = FramePerfect;
	//	}
	//	/* 将整帧拷贝到公共队列区 */
	//	OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
	//	/* 清空临时缓存区 */
	//	OSCRecByteQueue->Queue1.clear();

	//}
	//else
	//{
	//	/* 将新数据存入临时缓存区 */
	//	OSCRecByteQueue->Queue1.push_back(rRecByte);
	//}
	//Sa1 = Temp1->Timer();
	//if (Sa1 >= 2000)
	//{
	//	printf("D      %d\n", Sa1);
	//}
	//if (NoComplete != State)
	{
		/* 申请一个内存区 */
		NewMemory = DataSpace->UseSpace();
		if (ErrUint != NewMemory)
		{
			/* 组装业务申请消息 */
			DataSpace->MsgWrite(NewMemory, MsgUnHandle, 1, 0, OSCRecThreadNum, OSCSendThreadNum, TempData);
			/* 发送内存区地址 */
			OSCServiceSender->ServiceSender(NewMemory);
		}
	}
	return TRUE;
}


bool SFirAnalysis::FirConfirm(void)
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	///* 是否大于等于4个字节*/
	//if (bIsSuccess)
	//{
	//	if (4 > OSCRecByteQueue->Queue1.size()) {
	//		bIsSuccess = FALSE; }
	//}
	///* 是否为指定帧头*/
	//if (bIsSuccess)
	//{
	//	if (ProFir_Header != OSCRecByteQueue->Queue1[0]) {
	//		bIsSuccess = FALSE; }
	//}
	///* 是否为指定帧尾*/
	//if (bIsSuccess)
	//{
	//	if (ProFir_End != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 1]) {
	//		bIsSuccess = FALSE; }
	//}
	///* 校验和是否正确*/
	//if (bIsSuccess)
	//{
	//	char CheckBuff = 0;

	//	for (UINT i = 0; i < OSCRecByteQueue->Queue1.size() - 2; i++)
	//	{
	//		CheckBuff += OSCRecByteQueue->Queue1[i];
	//	}
	//	if (CheckBuff != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 2]) {
	//		bIsSuccess = FALSE; }
	//}

	return (TRUE == bIsSuccess);
}