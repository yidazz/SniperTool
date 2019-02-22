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



UINT WINAPI RTWork(void* pParam)
{
	MESSAGE *V;
	uint a1 = 0;
	int ia1 = 0;
	RTTimerUs->Zero();
	// 线程循环
	while (!RTMThread->SExit)
	{
		a1 = RTTimerUs->Timer();
		if (a1 >= 1000 && ++ia1 == 1)
		{
			printf("%d\n", (a1 / ia1));
			a1 = 0;
			ia1 = 0;
		}
		RTTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector[RTThreadNum] = TRUE;
		if (0 != RTInVector->Count)
		{/*
			a1 += RTInVector.size();
			if (800 == ia1++)
			{
				printf("                 %d\n", (a1 / ia1));
				a1 = 0;
				ia1 = 0;
			}*/
			V = RTInVector->PopFront();
			switch (V->DestNum)
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* 将消息地址推入转发器入口 */
					OSCSendInVector->PushBack(V);
					break;
				case OSCRecThreadNum:
					/* 将消息地址推入转发器入口 */
					OSCRecInVector->PushBack(V);
					break;
				default:break;
			}

			//system("cls");
			//printf("1:%d \n",RTInVector[0]);
			//V = RTInVector[0];
			//printf("2: ");
			//	
			//for (UINT i = 0; i < V->Data.size(); i++)
			//{
			//	printf("%X ", V->Data[i]);
			//}
			//printf("\n");
			//delete V;
			//RTInVector.erase(RTInVector.begin());

			/** 进入临界段 */
			//EnterCriticalSection(&RTInVector->S_csVector2);

			//switch (RTInVecto[0])
			//{
			//	case OSCSendModNum: 
			//		/** 进入临界段 */
			//		EnterCriticalSection(&OSCSendInVector->S_csVector2);
			//		OSCSendInVector->Queue2.push_back(RTInVector[0]);
			//		RTInVector.erase(RTInVector.begin());
			//		/** 离开临界段 */
			//		LeaveCriticalSection(&OSCSendInVector->S_csVector2);
			//		break;
			//	case OSCRecModNum:
			//		/** 进入临界段 */
			//		EnterCriticalSection(&OSCRecInVector->S_csVector2);
			//		OSCRecInVector->Queue2.push_back(RTInVector->Queue2[0]);
			//		RTInVector->Queue2.erase(RTInVector->Queue2.begin());
			//		/** 离开临界段 */
			//		LeaveCriticalSection(&OSCRecInVector->S_csVector2);
			//		break;
			//	default:break;
			//}
			/** 离开临界段 */
			//LeaveCriticalSection(&RTInVector->S_csVector2);
		}
	}
	return 0;
}

