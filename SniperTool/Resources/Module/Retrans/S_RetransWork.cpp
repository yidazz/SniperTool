#include "S_RetransWork.h"

/* 使用一个线程资源 */
extern SThread *RTMThread;

/* 使用一个微秒定时器资源 */
extern STimerUs *RTTimerUs;

/* 使用一个入口队列缓存区资源 */
extern SVector *RTInVector;

/* 使用一个看门狗队列资源 */
extern SVector *WatchDogVector;


UINT WINAPI RTWork(void* pParam)
{
	// 线程循环
	while (!RTMThread->SExit)
	{
		/* 喂狗 */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;

		if (NULL != RTInVector->Queue2.size())
		{
			switch (RTInVector->Queue2[0][InDest])
			{
				case OSCSendModNum: break;
				case OSCRecModNum: break;
				default:break;
			}
		}
	}
	return 0;
}

