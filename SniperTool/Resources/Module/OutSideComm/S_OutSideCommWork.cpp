#include "S_OutSideCommWork.h"

/* ʹ�������߳���Դ */
extern SThread *OSCSendThread;
extern SThread *OSCRecThread;

/* ʹ��һ���ⲿ������ѡ������Դ */
extern SOutSideCommSelect *OSCOutSideCommSelect;
/* ʹ��һ��������Դ */
extern SSerialPort *OSCSerialPort;

/* ʹ��һ��֡������ѡ������Դ */
extern SByteAnalySelect *OSCByteAnalySelect;
/* ʹ��һ��֡��������Դ */
extern SFirAnalysis *OSCFirAnalysis;

/* ʹ��һ��ҵ��������Դ */
extern SServiceSender *OSCServiceSender;

/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCSendInVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCRecInVector;
/* ʹ��һ��ת������ڶ��л�������Դ */
extern SMsgQue *RTInVector;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCSendTimerUs;
/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCRecTimerUs;

/* ʹ��һ����Ϣ�ڴ���Դ */
extern SDataSpace *DataSpace;
/* ʹ��һ�����Ź�������Դ */
extern char WatchDogVector[ThreadNumTotal];


UINT WINAPI OSCRecThreadWork(void* pParam)
{
	uint a1 = 0;
	int ia1 = 0;
	/** ��ʱ�����ȡ���뻺������һ���ֽڵ����� */
	char cRecByte = NULL;

	OSCRecTimerUs->Zero();
	// �߳�ѭ��
	while (!OSCRecThread->SExit)
	{
		a1 = OSCRecTimerUs->Timer();
		if (a1 >= 100000 && ++ia1 == 1)
		{
			printf("               %d\n", (a1 / ia1));
			a1 = 0;
			ia1 = 0;
		}
		OSCRecTimerUs->Zero();
		/* ι�� */
		WatchDogVector[OSCRecThreadNum] = TRUE;
		/** ��ȡ���뻺������һ���ֽڵ����� */
		//if (TRUE == OSCOutSideCommSelect->OutSideCommRecSelect(cRecByte))
		{
			/** ֡������ */

			/** ���յ��ֽڴ���֡������*/
			OSCByteAnalySelect->AnalysisSelect(cRecByte);
			Sleep(0.5);
		}
	}
	return 0;
}

UINT WINAPI OSCSendThreadWork(void* pParam)
{
	unsigned int V;
	uint a1=0;
	int ia1 = 0;
	OSCSendTimerUs->Zero();
	 //�߳�ѭ��,��ѯ��ʽ��ȡ��������  
	while (!OSCSendThread->SExit)
	{
		a1 = OSCSendTimerUs->Timer();
		if (a1 >= 10000 && ++ia1 == 1)
		{
			printf("                                  %d\n", (a1/ia1));
			a1 = 0;
			ia1 = 0;
		}
		OSCSendTimerUs->Zero();
		/* ι�� */
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

		/** ��ȡ���뻺�����еĵ�ַ������ */
		//WriteData(data, 3);
	}

	return 0;
}

