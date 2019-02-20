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

/* ʹ��һ��ҵ���Ͷ��л�������Դ */
extern SVector *OSCSendBuffVector;
/* ʹ��һ���ⲿ�ֽڽ��ն��л�������Դ */
extern SVector *OSCRecByteQueue;
/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csOSCSendIn;   //������
/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csOSCRecIn;   //������
/* ʹ��һ��������ڶ��л�������Դ */
extern vector <MESSAGE*> OSCSendInBuffVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern vector <MESSAGE*> OSCRecInBuffVector;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCSendTimerUs;
/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCRecTimerUs;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;

/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csRTIn;   //������

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
		if (a1 >= 2000)
		{
			printf("                 %d\n", a1);
		}
		OSCRecTimerUs->Zero();
		/* ι�� */
		WatchDogVector->Queue1[OSCRecThreadNum] = TRUE;
		/** ��ȡ���뻺������һ���ֽڵ����� */
		if (TRUE == OSCOutSideCommSelect->OutSideCommRecSelect(cRecByte))
		{
			/** ֡������ */

			/** ���յ��ֽڴ���֡������*/
			OSCByteAnalySelect->AnalysisSelect(cRecByte);
		}

		/** ҵ������ */

		/** ����Ҫ������ģ�������ҵ�񷢸�����ת���� */
		//if (TRUE != OSCServiceSender->ServiceSender())
		//{
		//	/* ���ʹ��� */
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
	 //�߳�ѭ��,��ѯ��ʽ��ȡ��������  
	while (!OSCSendThread->SExit)
	{
		a1 = OSCSendTimerUs->Timer();
		if (a1 >= 2000)
		{
			printf("                                        %d\n", a1);
		}
		OSCSendTimerUs->Zero();
		/* ι�� */
		WatchDogVector->Queue1[OSCSendThreadNum] = TRUE;

		/* �����ٽ�� */
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
			/* ����Ѿ�ת���ĵ�ַ */
			OSCSendInBuffVector.erase(OSCSendInBuffVector.begin());
			/** �뿪�ٽ�� */
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
			/** �뿪�ٽ�� */
			LeaveCriticalSection(&S_csOSCSendIn);
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

