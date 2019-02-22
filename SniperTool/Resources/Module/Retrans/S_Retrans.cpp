#include "S_Retrans.h"

/** ת������������*/
extern UINT WINAPI RTWork(void* pParam);

/* ʹ��һ���߳���Դ */
SThread *RTMThread = new SThread;

/* ʹ��һ��΢�붨ʱ����Դ */
STimerUs *RTTimerUs = new STimerUs;

/* ʹ��һ��ת������ڶ��л�������Դ */
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
	/** �Ƿ��д����� */
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
	/** ��ʼ���߳�ת����ģ��ʧ��  �ر�ģ��  ������ */
	if (!bIsSuccess)
	{
		RTMThread->EndThread();
		return FALSE;
	}
	return TRUE;
}

bool RetransModule::EndRTM()
{
	/** �ر������߳��봮�� */
	RTMThread->EndThread();

	return TRUE;
}

