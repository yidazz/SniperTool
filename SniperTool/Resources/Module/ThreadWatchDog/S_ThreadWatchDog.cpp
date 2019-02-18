#include "S_ThreadWatchDog.h"

/** ���Ź���������*/
extern UINT WINAPI TWDWork(void* pParam);

/* ʹ��һ���߳���Դ */
SThread *TWDThread = new SThread;

/* ʹ��һ�����Ź�������Դ */
SVector *WatchDogVector = new SVector;

/* ��ʱʹ��һ���洢�����е��̺߳ŵĶ�����Դ */
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
	/** �Ƿ��д����� */
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
	/** ��ʼ���߳̿��Ź�ģ��ʧ��  �ر�ģ��  ������ */
	if (!bIsSuccess)
	{
		TWDThread->EndThread();
		return FALSE;
	}
	return TRUE;
}

bool ThreadWatchDogModule::EndTWDM()
{
	/** �ر������߳� */
	TWDThread->EndThread();

	return TRUE;
}




