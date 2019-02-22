#include "S_ThreadWatchDogWork.h"

/* ʹ��һ����Ϣ�ڴ���Դ */
extern SDataSpace *DataSpace;
/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCSendInVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCRecInVector;
/* ʹ��һ��ת������ڶ��л�������Դ */
extern SMsgQue *RTInVector;

/* ʹ��һ���߳���Դ */
extern SThread *TWDThread;

/* ʹ��һ�����Ź�������Դ */
extern char WatchDogVector[ThreadNumTotal];

extern OutSideCommModule *SS3;
extern ThreadWatchDogModule *SS4;
extern RetransModule *SS5;

UINT WINAPI TWDWork(void* pParam)
{
	int a=0,b=0,c=0,d=0,e=0;

	// �߳�ѭ��
	while (!TWDThread->SExit)
	{
		if (DataSpace->Count > 300)
		{
			printf("1                                                              %d\n", DataSpace->Count);
		}
		if (RTInVector->Count > 300)
		{
			printf("2                                                            %d\n", RTInVector->Count);
		}
		if (OSCRecInVector->Count > 300)
		{
			printf("3                                                             %d\n", OSCRecInVector->Count);
		}
		if (OSCSendInVector->Count > 300)
		{
			printf("4                                                             %d\n", OSCSendInVector->Count);
		}

		Sleep(1000);
		for (uint i = 0;i < ThreadNumTotal;i++)
		{
			if (TWDThreadNum == i || NoThreadNum == i) { continue; }           //�����߳̿��Ź��߳�
			if (TRUE != WatchDogVector[i])
			{
				qDebug("Thread Error: %d", i);
				//qDebug() << SS3->EndOSCM();
				//qDebug() << SS3->CloseSerialPort();
				//qDebug() << SS5->EndRTM();
				//system("pause");
			}
			WatchDogVector[i] = FALSE;
		}
	}
	return 0;
}
