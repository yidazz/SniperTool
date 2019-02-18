#include "S_Thread.h"  

SThread::SThread(void)
{
	mThread = INVALID_HANDLE_VALUE;
	SThreadId = NULL;
	SExit = FALSE;
}

SThread::~SThread(void)
{
	EndThread();
}

bool SThread::CreateThread(_beginthreadex_proc_type ThreadWork)
{
	/** ����߳��Ƿ��Ѿ������� */
	if (mThread != INVALID_HANDLE_VALUE)
	{
		/** �߳��Ѿ����� */
		return FALSE;
	}
	SExit = FALSE;
	/** �����߳� */
	mThread = (HANDLE)_beginthreadex(NULL, 0, ThreadWork, this, 0, &SThreadId);
	if (!mThread)
	{
		return FALSE;
	}
	/** �����̵߳����ȼ�,������ͨ�߳� */
	//if (!SetThreadPriority(m_hSendThread, SeThreadPrio))
	//{
	//	return FALSE;
	//}

	return TRUE;
}


bool SThread::EndThread()
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	/** ����߳��Ƿ��Ѿ������� */
	if (INVALID_HANDLE_VALUE == mThread)
	{
		bIsSuccess = FALSE;
	}
	if (bIsSuccess)
	{
		/** ֪ͨ�߳��˳� */
		SExit = TRUE;

		/** �ȴ��߳��˳� */
		WaitForSingleObject(mThread, INFINITE);

		/** ���߳̾����Ч */
		bIsSuccess = CloseHandle(mThread);

		mThread = INVALID_HANDLE_VALUE;
	}
	return (TRUE == bIsSuccess);
}