#include "S_Retrans.h"

/** 转发器监听函数*/
extern UINT WINAPI RTWork(void* pParam);

/* 使用一个线程资源 */
SThread *RTMThread = new SThread;

/* 使用一个微秒定时器资源 */
STimerUs *RTTimerUs = new STimerUs;

/* 使用一个入口队列互斥量资源 */
CRITICAL_SECTION S_csRTIn;   //互斥量
/* 使用一个入口队列缓存区资源 */
vector <MESSAGE*> RTInVector;

RetransModule::RetransModule()
{
	InitializeCriticalSection(&S_csRTIn);
	ErrCode = NoError;
}

RetransModule::~RetransModule()
{
	DeleteCriticalSection(&S_csRTIn);
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

