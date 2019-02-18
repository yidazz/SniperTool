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
	/** 创建线程 */
	bool CreateThread(_beginthreadex_proc_type ThreadWork);

	/** 关闭线程 */
	bool EndThread();

public:
	/** 线程退出标志 */
	bool SExit;

private:
	/** 线程句柄 */
	volatile HANDLE mThread;

	/** 线程ID */
	UINT SThreadId;
};


#endif  //S_THREAD_H_