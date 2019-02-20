#include "S_Retrans.h"

/** ת������������*/
extern UINT WINAPI RTWork(void* pParam);

/* ʹ��һ���߳���Դ */
SThread *RTMThread = new SThread;

/* ʹ��һ��΢�붨ʱ����Դ */
STimerUs *RTTimerUs = new STimerUs;

/* ʹ��һ����ڶ��л�������Դ */
CRITICAL_SECTION S_csRTIn;   //������
/* ʹ��һ����ڶ��л�������Դ */
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

