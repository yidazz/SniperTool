#include "S_RetransWork.h"

/* 使用一个业务发送器资源 */
extern SServiceSender *OSCServiceSender;
/* 使用一个线程资源 */
extern SThread *RTMThread;

/* 使用一个微秒定时器资源 */
extern STimerUs *RTTimerUs;

/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csRTIn;   //互斥量
/* 使用一个入口队列缓存区资源 */
extern vector <MESSAGE*> RTInVector;

/* 使用一个看门狗队列资源 */
extern SVector *WatchDogVector;

/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csOSCSendIn;   //互斥量
/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csOSCRecIn;   //互斥量
/* 使用一个发送入口队列缓存区资源 */
extern vector <MESSAGE*> OSCSendInBuffVector;
/* 使用一个接收入口队列缓存区资源 */
extern vector <MESSAGE*> OSCRecInBuffVector;



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
		if (a1 >= 2000)
		{
			printf("%d\n", a1);
		}
		RTTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;
		/* 进入临界段 */
		EnterCriticalSection(&S_csRTIn);
		if (NULL != RTInVector.size())
		{/*
			a1 += RTInVector.size();
			if (800 == ia1++)
			{
				printf("                 %d\n", (a1 / ia1));
				a1 = 0;
				ia1 = 0;
			}*/
			V = RTInVector[0];
			/* 清除已经转发的地址 */
			RTInVector.erase(RTInVector.begin());
			/** 离开临界段 */
			LeaveCriticalSection(&S_csRTIn);
			switch (V->DestNum)
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* 进入临界段 */
					EnterCriticalSection(&S_csOSCSendIn);
					/* 将消息地址推入转发器入口 */
					OSCSendInBuffVector.push_back(V);
					/** 离开临界段 */
					LeaveCriticalSection(&S_csOSCSendIn);
					break;
				case OSCRecThreadNum:
					/* 进入临界段 */
					EnterCriticalSection(&S_csOSCRecIn);
					/* 将消息地址推入转发器入口 */
					OSCRecInBuffVector.push_back(V);
					/** 离开临界段 */
					LeaveCriticalSection(&S_csOSCRecIn);
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
			//		EnterCriticalSection(&OSCSendInBuffVector->S_csVector2);
			//		OSCSendInBuffVector->Queue2.push_back(RTInVector[0]);
			//		RTInVector.erase(RTInVector.begin());
			//		/** 离开临界段 */
			//		LeaveCriticalSection(&OSCSendInBuffVector->S_csVector2);
			//		break;
			//	case OSCRecModNum:
			//		/** 进入临界段 */
			//		EnterCriticalSection(&OSCRecInBuffVector->S_csVector2);
			//		OSCRecInBuffVector->Queue2.push_back(RTInVector->Queue2[0]);
			//		RTInVector->Queue2.erase(RTInVector->Queue2.begin());
			//		/** 离开临界段 */
			//		LeaveCriticalSection(&OSCRecInBuffVector->S_csVector2);
			//		break;
			//	default:break;
			//}
			/** 离开临界段 */
			//LeaveCriticalSection(&RTInVector->S_csVector2);
		}
		else
		{
			/** 离开临界段 */
			LeaveCriticalSection(&S_csRTIn);
		}
	}
	return 0;
}

