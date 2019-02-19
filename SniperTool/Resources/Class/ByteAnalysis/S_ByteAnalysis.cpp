#include "S_ByteAnalysis.h"

/* 使用一个外部字节接收队列缓存区资源 */
extern SVector *OSCRecByteQueue;
/* 使用一个业务发送队列缓存区资源 */
extern SVector *OSCSendBuffVector;

vector<char> a1 = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 };

SFirAnalysis::SFirAnalysis()
{
}

SFirAnalysis::~SFirAnalysis()
{
}

bool SFirAnalysis::FirAnalysis(char &rRecByte)
{
	int State = NoComplete;
	/** 收到帧的开头 */
	if (ProFir_Header == rRecByte)
	{
		/** 判断缓存区中是否有残缺数据 */
		if (NULL != OSCRecByteQueue->Queue1.size())
		{
			/* 有残缺数据 则拷贝到数据队列缓存区 */
			OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
			/* 清空临时缓存区 */
			OSCRecByteQueue->Queue1.clear();
			/* 将新数据存入临时缓存区 */
			OSCRecByteQueue->Queue1.push_back(rRecByte);
			/* 收到错误数据 */
			State = FrameError;
		}
		else
		{
			/* 将新数据存入临时缓存区 */
			OSCRecByteQueue->Queue1.push_back(rRecByte);
		}
	}
	/** 收到帧的结尾 */
	else if (ProFir_End == rRecByte)
	{
		/* 将新数据存入临时缓存区 */
		OSCRecByteQueue->Queue1.push_back(rRecByte);
		/* 判断帧是否满足条件 */
		if(TRUE!= FirConfirm())
		{
			/* 收到错误数据 */
			State = FrameError;
		}
		else
		{
			/* 收到完整数据 */
			State = FramePerfect;
		}
		/* 将整帧拷贝到公共队列区 */
		OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
		/* 清空临时缓存区 */
		OSCRecByteQueue->Queue1.clear();

	}
	else
	{
		/* 将新数据存入临时缓存区 */
		OSCRecByteQueue->Queue1.push_back(rRecByte);
	}
	if (NoComplete != State)
	{
		/* 组装业务申请消息 */
		OSCSendBuffVector->Queue2.push_back(a1);
	}
	return TRUE;
}


bool SFirAnalysis::FirConfirm(void)
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	/* 是否大于等于4个字节*/
	if (bIsSuccess)
	{
		if (4 > OSCRecByteQueue->Queue1.size()) {
			bIsSuccess = FALSE; }
	}
	/* 是否为指定帧头*/
	if (bIsSuccess)
	{
		if (ProFir_Header != OSCRecByteQueue->Queue1[0]) {
			bIsSuccess = FALSE; }
	}
	/* 是否为指定帧尾*/
	if (bIsSuccess)
	{
		if (ProFir_End != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 1]) {
			bIsSuccess = FALSE; }
	}
	/* 校验和是否正确*/
	if (bIsSuccess)
	{
		char CheckBuff = 0;

		for (UINT i = 0; i < OSCRecByteQueue->Queue1.size() - 2; i++)
		{
			CheckBuff += OSCRecByteQueue->Queue1[i];
		}
		if (CheckBuff != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 2]) {
			bIsSuccess = FALSE; }
	}

	return (TRUE == bIsSuccess);
}