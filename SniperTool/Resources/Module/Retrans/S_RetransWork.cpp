#include "S_RetransWork.h"

/* 使用一个线程资源 */
extern SThread *RTMThread;

/* 使用一个微秒定时器资源 */
extern STimerUs *RTTimerUs;

/* 使用一个入口队列缓存区资源 */
extern vector <MESSAGE*> RTInVector;

/* 使用一个看门狗队列资源 */
extern SVector *WatchDogVector;

/* 使用一个发送入口队列缓存区资源 */
extern SVector *OSCSendInBuffVector;
/* 使用一个接收入口队列缓存区资源 */
extern SVector *OSCRecInBuffVector;



UINT WINAPI RTWork(void* pParam)
{
	
	// 线程循环
	while (!RTMThread->SExit)
	{
		/* 喂狗 */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;

		if (NULL != RTInVector.size())
		{
			system("cls");
			printf("1:%d \n",RTInVector[0]);
			MESSAGE *V = RTInVector[0];
			printf("2: ");
				
			for (UINT i = 0; i < V->Data.size(); i++)
			{
				printf("%X ", V->Data[i]);
			}
			printf("\n");
			delete V;
			RTInVector.erase(RTInVector.begin());

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
	}
	return 0;
}

