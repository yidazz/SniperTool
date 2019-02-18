#include "S_ThreadWatchDog.h"

/** 看门狗监听函数*/
extern UINT WINAPI TWDWork(void* pParam);

/* 使用一个线程资源 */
SThread *TWDThread = new SThread;

/* 使用一个看门狗队列资源 */
SVector *WatchDogVector = new SVector;

/* 暂时使用一个存储工作中的线程号的队列资源 */
SVector *WorkingThreadNum = new SVector;

ThreadWatchDogModule::ThreadWatchDogModule()
{
	for (int i = 0;i < ThreadNumTotal;i++)
	{
		WorkingThreadNum->Queue1.push_back(i);
	}
	WatchDogVector->Queue1.insert(WatchDogVector->Queue1.begin(), ThreadNumTotal ,0);
}

ThreadWatchDogModule::~ThreadWatchDogModule()
{

}

bool ThreadWatchDogModule::InitTWDM()
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;
	ErrCode = NoError;

	if (bIsSuccess)
	{
		bIsSuccess = TWDThread->CreateThread(TWDWork);
		if (!bIsSuccess)
		{
			if (NoError != ErrCode) { ErrCode = TWDM_CreateThread; }
		}
	}
	/** 初始化线程看门狗模块失败  关闭模块  并返回 */
	if (!bIsSuccess)
	{
		TWDThread->EndThread();
		return FALSE;
	}
	return TRUE;
}

bool ThreadWatchDogModule::EndTWDM()
{
	/** 关闭所有线程 */
	TWDThread->EndThread();

	return TRUE;
}




