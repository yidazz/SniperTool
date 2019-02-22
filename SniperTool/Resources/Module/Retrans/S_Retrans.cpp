#include "S_Retrans.h"

/** 转发器监听函数*/
extern UINT WINAPI RTWork(void* pParam);

/* 使用一个线程资源 */
SThread *RTMThread = new SThread;

/* 使用一个微秒定时器资源 */
STimerUs *RTTimerUs = new STimerUs;

/* 使用一个转发器入口队列缓存区资源 */
SMsgQue *RTInVector = new SMsgQue;

RetransModule::RetransModule()
{
	ErrCode = NoError;
}

RetransModule::~RetransModule()
{
	ErrCode = NoError;
	EndRTM();
}

bool RetransModule::InitRTM()
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;
	ErrCode = NoError;

	if (bIsSuccess)
	{
		bIsSuccess = RTMThread->CreateThread(RTWork);
		if (!bIsSuccess)
		{
			if (NoError != ErrCode) { ErrCode = RTM_CreateThread; }
		}
	}
	/** 初始化线程转发器模块失败  关闭模块  并返回 */
	if (!bIsSuccess)
	{
		RTMThread->EndThread();
		return FALSE;
	}
	return TRUE;
}

bool RetransModule::EndRTM()
{
	/** 关闭所有线程与串口 */
	RTMThread->EndThread();

	return TRUE;
}

