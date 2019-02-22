#pragma once
#ifndef S_THREADWATCHDOG_H_  
#define S_THREADWATCHDOG_H_  

#include <Windows.h>  
#include "ErrorTable.h"
#include "S_Thread.h"
#include "S_Queue.h"
#include "Protocol.h"

/** 线程看门狗模块类
*
*  本类实现了各个模块线程的堵塞判断的基本功能
*
*/

class ThreadWatchDogModule
{
public:
	ThreadWatchDogModule();
	~ThreadWatchDogModule();

public:
	/** 打开线程看门狗模块*/
	bool InitTWDM();

	/** 关闭线程看门狗模块*/
	bool EndTWDM();

public:
	/**错误码*/
	ErrorTable ErrCode;
};

#endif //S_THREADWATCHDOG_H_ 
