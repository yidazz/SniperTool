#include "S_ThreadWatchDogWork.h"

/* 使用一个线程资源 */
extern SThread *TWDThread;

/* 使用一个看门狗队列资源 */
extern SVector *WatchDogVector;

/* 暂时使用一个存储工作中的线程号的队列资源 */
extern SVector *WorkingThreadNum;

UINT WINAPI TWDWork(void* pParam)
{
	// 线程循环
	while (!TWDThread->SExit)
	{
		Sleep(100);
		for (uint i = 0;i < WorkingThreadNum->Queue1.size();i++)
		{
			if (TWDThreadNum == WorkingThreadNum->Queue1[i]) { continue; }           //跳过线程看门狗线程
			if (TRUE != WatchDogVector->Queue1[WorkingThreadNum->Queue1[i]])
			{
				qDebug("Thread Error: %d", WorkingThreadNum->Queue1[i]);
			}
			WatchDogVector->Queue1[WorkingThreadNum->Queue1[i]] = FALSE;
		}
	}
	return 0;
}
