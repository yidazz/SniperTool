#include "S_OutSideCommWork.h"

/* 使用两个线程资源 */
extern SThread *OSCSendThread;
extern SThread *OSCRecThread;

/* 使用一个外部交流器选择器资源 */
extern SOutSideCommSelect *OSCOutSideCommSelect;
/* 使用一个串口资源 */
extern SSerialPort *OSCSerialPort;

/* 使用一个帧分析器选择器资源 */
extern SByteAnalySelect *OSCByteAnalySelect;
/* 使用一个帧分析器资源 */
extern SFirAnalysis *OSCFirAnalysis;

/* 使用一个业务发送器资源 */
extern SServiceSender *OSCServiceSender;

/* 使用一个发送入口队列缓存区资源 */
extern SMsgQue *OSCSendInVector;
/* 使用一个接收入口队列缓存区资源 */
extern SMsgQue *OSCRecInVector;
/* 使用一个转发器入口队列缓存区资源 */
extern SMsgQue *RTInVector;

/* 使用一个微秒定时器资源 */
extern STimerUs *OSCSendTimerUs;
/* 使用一个微秒定时器资源 */
extern STimerUs *OSCRecTimerUs;

/* 使用一个消息内存资源 */
extern SDataSpace *DataSpace;
/* 使用一个看门狗队列资源 */
extern char WatchDogVector[ThreadNumTotal];


UINT WINAPI OSCRecThreadWork(void* pParam)
{
	uint a1 = 0;
	int ia1 = 0;
	/** 临时储存读取输入缓冲区中一个字节的数据 */
	char cRecByte = NULL;

	OSCRecTimerUs->Zero();
	// 线程循环
	while (!OSCRecThread->SExit)
	{
		a1 = OSCRecTimerUs->Timer();
		if (a1 >= 1000 && ++ia1 == 1)
		{
			printf("               %d\n", (a1 / ia1));
			a1 = 0;
			ia1 = 0;
		}
		OSCRecTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector[OSCRecThreadNum] = TRUE;
		/** 读取输入缓冲区中一个字节的数据 */
		if (TRUE == OSCOutSideCommSelect->OutSideCommRecSelect(cRecByte))
		{
			/** 帧分析器 */

			/** 接收到字节传入帧分析器*/
			OSCByteAnalySelect->AnalysisSelect(cRecByte);
		}
	}
	return 0;
}

UINT WINAPI OSCSendThreadWork(void* pParam)
{
	MESSAGE *V;
	uint a1=0;
	int ia1 = 0;
	OSCSendTimerUs->Zero();
	 //线程循环,轮询方式读取串口数据  
	while (!OSCSendThread->SExit)
	{
		a1 = OSCSendTimerUs->Timer();
		if (a1 >= 1000 && ++ia1 == 1)
		{
			printf("                                  %d\n", (a1/ia1));
			a1 = 0;
			ia1 = 0;
		}
		OSCSendTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector[OSCSendThreadNum] = TRUE;
		if (0 != OSCSendInVector->Count)
		{
			//a1 += OSCSendInVector.size();
			//if (800 == ia1++)
			//{
			//	printf("XXXXXXXXXXX %d\n", (a1/ia1));
			//	a1 = 0;
			//	ia1 = 0;
			//}
			V = OSCSendInVector->PopFront();
			DataSpace->SpaceDel(V);

			//system("cls");
			//printf("1:%d \n",V);
			//printf("2: ");
			//for (UINT i = 0; i < V->Data.size(); i++)
			//{
			//	printf("%X ", V->Data[i]);
			//}
			//printf("\n");
		}
		//qDebug() << mTimerUs->Timer();
		//qDebug() << mTimerUs->Timer();
		//UINT BytesInQue = pSerialPort->GetBytesInCOM();
		//if (0 == BytesInQue)
		//{
		//	continue;
		//}

		/** 读取输入缓冲区中的地址并发送 */
		//WriteData(data, 3);
	}

	return 0;
}

