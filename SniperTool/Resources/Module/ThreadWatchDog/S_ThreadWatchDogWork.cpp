#include "S_ThreadWatchDogWork.h"

/* 使用一个消息内存资源 */
extern SDataSpace *DataSpace;
/* 使用一个发送入口队列缓存区资源 */
extern SMsgQue *OSCSendInVector;
/* 使用一个接收入口队列缓存区资源 */
extern SMsgQue *OSCRecInVector;
/* 使用一个转发器入口队列缓存区资源 */
extern SMsgQue *RTInVector;

/* 使用一个线程资源 */
extern SThread *TWDThread;

/* 使用一个看门狗队列资源 */
extern char WatchDogVector[ThreadNumTotal];

extern OutSideCommModule *SS3;
extern ThreadWatchDogModule *SS4;
extern RetransModule *SS5;

UINT WINAPI TWDWork(void* pParam)
{
	int a=0,b=0,c=0,d=0,e=0;

	// 线程循环
	while (!TWDThread->SExit)
	{
		//if (DataSpace->Count >= 00)
		//{
		//	printf("%d\n", DataSpace->Count);
		//}
		if (DataSpace->Count >= 900)
		{
			printf("%d\n", DataSpace->Count);
			SS3->EndOSCM();
			SS3->CloseSerialPort();
			SS5->EndRTM();
			system("pause");
		}
		//if (RTInVector->Count > 200)
		//{
		//	printf("2                                                            %d\n", RTInVector->Count);
		//}
		//if (OSCRecInVector->Count > 200)
		//{
		//	printf("3                                                             %d\n", OSCRecInVector->Count);
		//}
		//if (OSCSendInVector->Count > 200)
		//{
		//	printf("4                                                             %d\n", OSCSendInVector->Count);
		//}

		//Sleep(1000);
		//for (uint i = 0;i < ThreadNumTotal;i++)
		//{
		//	if (TWDThreadNum == i || NoThreadNum == i) { continue; }           //跳过线程看门狗线程
		//	if (TRUE != WatchDogVector[i])
		//	{
		//		qDebug("Thread Error: %d", i);
		//		//qDebug() << SS3->EndOSCM();
		//		//qDebug() << SS3->CloseSerialPort();
		//		//qDebug() << SS5->EndRTM();
		//		//system("pause");
		//	}
		//	WatchDogVector[i] = FALSE;
		//}
	}
	return 0;
}
