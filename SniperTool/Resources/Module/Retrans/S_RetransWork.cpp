#include "S_RetransWork.h"

/* 使用一个业务发送器资源 */
extern SServiceSender *OSCServiceSender;
/* 使用一个线程资源 */
extern SThread *RTMThread;

/* 使用一个微秒定时器资源 */
extern STimerUs *RTTimerUs;

/* 使用一个入口队列缓存区资源 */
extern SMsgQue *RTInVector;

/* 使用一个看门狗队列资源 */
extern char WatchDogVector[ThreadNumTotal];

/* 使用一个发送入口队列缓存区资源 */
extern SMsgQue *OSCSendInVector;
/* 使用一个接收入口队列缓存区资源 */
extern SMsgQue *OSCRecInVector;

/* 使用一个消息内存资源 */
extern SDataSpace *DataSpace;



UINT WINAPI RTWork(void* pParam)
{
	unsigned int RTMsgIndexBuff = 0;
	
	// 线程循环
	while (!RTMThread->SExit)
	{
		/* 喂狗 */
		WatchDogVector[RTThreadNum] = TRUE;
		if (0 != RTInVector->Count)
		{
			RTMsgIndexBuff = RTInVector->PopFront();
			switch (DataSpace->MsgReadDest(RTMsgIndexBuff))
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* 将消息地址推入发送线程入口 */
					OSCSendInVector->PushBack(RTMsgIndexBuff);
					break;
				case OSCRecThreadNum:
					/* 将消息地址推入接收线程入口 */
					OSCRecInVector->PushBack(RTMsgIndexBuff);
					break;
				default:break;
			}
		}
	}
	return 0;
}

