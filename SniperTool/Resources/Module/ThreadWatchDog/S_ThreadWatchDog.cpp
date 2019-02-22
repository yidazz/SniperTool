#include "S_ThreadWatchDog.h"

/** ���Ź���������*/
extern UINT WINAPI TWDWork(void* pParam);

/* ʹ��һ���߳���Դ */
SThread *TWDThread = new SThread;

/* ʹ��һ�����Ź�������Դ */
char WatchDogVector[ThreadNumTotal];

ThreadWatchDogModule::ThreadWatchDogModule()
{
	for (int i = 0;i < ThreadNumTotal;i++)
	{
		WatchDogVector[i] = TRUE;
	}
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




