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
	/** 检测线程是否已经开启了 */
	if (mThread != INVALID_HANDLE_VALUE)
	{
		/** 线程已经开启 */
		return FALSE;
	}
	SExit = FALSE;
	/** 开启线程 */
	mThread = (HANDLE)_beginthreadex(NULL, 0, ThreadWork, this, 0, &SThreadId);
	if (!mThread)
	{
		return FALSE;
	}
	/** 设置线程的优先级,高于普通线程 */
	//if (!SetThreadPriority(m_hSendThread, SeThreadPrio))
	//{
	//	return FALSE;
	//}

	return TRUE;
}


bool SThread::EndThread()
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	/** 检测线程是否已经开启了 */
	if (INVALID_HANDLE_VALUE == mThread)
	{
		bIsSuccess = FALSE;
	}
	if (bIsSuccess)
	{
		/** 通知线程退出 */
		SExit = TRUE;

		/** 等待线程退出 */
		WaitForSingleObject(mThread, INFINITE);

		/** 置线程句柄无效 */
		bIsSuccess = CloseHandle(mThread);

		mThread = INVALID_HANDLE_VALUE;
	}
	return (TRUE == bIsSuccess);
}