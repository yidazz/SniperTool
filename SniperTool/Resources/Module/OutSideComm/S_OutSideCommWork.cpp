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
/* ʹ��һ��������ڶ��л�������Դ */
extern SVector *OSCSendInBuffVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern SVector *OSCRecInBuffVector;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCTimerUs;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;


UINT WINAPI OSCRecThreadWork(void* pParam)
{
	/** ��ʱ�����ȡ���뻺������һ���ֽڵ����� */
	char cRecByte = NULL;

	// �߳�ѭ��
	while (!OSCRecThread->SExit)
	{
		/* ι�� */
		WatchDogVector->Queue1[OSCRecThreadNum] = TRUE;
		/** ������ */
		
		/** ��ȡ���뻺������һ���ֽڵ����� */
		if (TRUE == OSCOutSideCommSelect->OutSideCommRecSelect(cRecByte))
		{
			/** ֡������ */

			/** ���յ��ֽڴ���֡������*/
			OSCByteAnalySelect->AnalysisSelect(cRecByte);
		}

		/** ҵ������ */

		/** ����Ҫ������ģ�������ҵ�񷢸�����ת���� */
		if (TRUE != OSCServiceSender->ServiceSender())
		{
			/* ���ʹ��� */
		}
	}
	return 0;
}

UINT WINAPI OSCSendThreadWork(void* pParam)
{
	 //�߳�ѭ��,��ѯ��ʽ��ȡ��������  
	while (!OSCSendThread->SExit)
	{
		/* ι�� */
		WatchDogVector->Queue1[OSCSendThreadNum] = TRUE;
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

