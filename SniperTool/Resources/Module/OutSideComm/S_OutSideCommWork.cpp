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

/* 使用一个业务发送队列缓存区资源 */
extern SVector *OSCSendBuffVector;
/* 使用一个外部字节接收队列缓存区资源 */
extern SVector *OSCRecByteQueue;
/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csOSCSendIn;   //互斥量
/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csOSCRecIn;   //互斥量
/* 使用一个发送入口队列缓存区资源 */
extern vector <MESSAGE*> OSCSendInBuffVector;
/* 使用一个接收入口队列缓存区资源 */
extern vector <MESSAGE*> OSCRecInBuffVector;

/* 使用一个微秒定时器资源 */
extern STimerUs *OSCSendTimerUs;
/* 使用一个微秒定时器资源 */
extern STimerUs *OSCRecTimerUs;

/* 使用一个看门狗队列资源 */
extern SVector *WatchDogVector;

/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csRTIn;   //互斥量

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
		if (a1 >= 2000)
		{
			printf("                 %d\n", a1);
		}
		OSCRecTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector->Queue1[OSCRecThreadNum] = TRUE;
		/** 读取输入缓冲区中一个字节的数据 */
		if (TRUE == OSCOutSideCommSelect->OutSideCommRecSelect(cRecByte))
		{
			/** 帧分析器 */

			/** 接收到字节传入帧分析器*/
			OSCByteAnalySelect->AnalysisSelect(cRecByte);
		}

		/** 业务发送器 */

		/** 将需要向其他模块申请的业务发给中心转发器 */
		//if (TRUE != OSCServiceSender->ServiceSender())
		//{
		//	/* 发送错误 */
		//}
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
		if (a1 >= 2000)
		{
			printf("                                        %d\n", a1);
		}
		OSCSendTimerUs->Zero();
		/* 喂狗 */
		WatchDogVector->Queue1[OSCSendThreadNum] = TRUE;

		/* 进入临界段 */
		EnterCriticalSection(&S_csOSCSendIn);
		if (NULL != OSCSendInBuffVector.size())
		{
			//a1 += OSCSendInBuffVector.size();
			//if (800 == ia1++)
			//{
			//	printf("XXXXXXXXXXX %d\n", (a1/ia1));
			//	a1 = 0;
			//	ia1 = 0;
			//}
			V = OSCSendInBuffVector[0];
			/* 清除已经转发的地址 */
			OSCSendInBuffVector.erase(OSCSendInBuffVector.begin());
			/** 离开临界段 */
			LeaveCriticalSection(&S_csOSCSendIn);
			//system("cls");
			//printf("1:%d \n",V);
			//printf("2: ");
			//for (UINT i = 0; i < V->Data.size(); i++)
			//{
			//	printf("%X ", V->Data[i]);
			//}
			//printf("\n");
			delete V;
		}
		else
		{
			/** 离开临界段 */
			LeaveCriticalSection(&S_csOSCSendIn);
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

