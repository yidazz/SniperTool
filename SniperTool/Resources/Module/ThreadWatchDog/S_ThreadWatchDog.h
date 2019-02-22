#pragma once
#ifndef S_THREADWATCHDOG_H_  
#define S_THREADWATCHDOG_H_  

#include <Windows.h>  
#include "ErrorTable.h"
#include "S_Thread.h"
#include "S_Queue.h"
#include "Protocol.h"

/** �߳̿��Ź�ģ����
*
*  ����ʵ���˸���ģ���̵߳Ķ����жϵĻ�������
*
*/

class ThreadWatchDogModule
{
public:
	ThreadWatchDogModule();
	~ThreadWatchDogModule();

public:
	/** ���߳̿��Ź�ģ��*/
	bool InitTWDM();

	/** �ر��߳̿��Ź�ģ��*/
	bool EndTWDM();

public:
	/**������*/
	ErrorTable ErrCode;
};

#endif //S_THREADWATCHDOG_H_ 
