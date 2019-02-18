#pragma once
#ifndef S_THREAD_H_  
#define S_THREAD_H_  

#include <Windows.h>  
#include <process.h>  


class SThread
{
public:
	SThread(void);
	~SThread(void);
public:
	/** �����߳� */
	bool CreateThread(_beginthreadex_proc_type ThreadWork);

	/** �ر��߳� */
	bool EndThread();

public:
	/** �߳��˳���־ */
	bool SExit;

private:
	/** �߳̾�� */
	volatile HANDLE mThread;

	/** �߳�ID */
	UINT SThreadId;
};


#endif  //S_THREAD_H_