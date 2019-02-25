#include "S_RetransWork.h"

/* ʹ��һ��ҵ��������Դ */
extern SServiceSender *OSCServiceSender;
/* ʹ��һ���߳���Դ */
extern SThread *RTMThread;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *RTTimerUs;

/* ʹ��һ����ڶ��л�������Դ */
extern SMsgQue *RTInVector;

/* ʹ��һ�����Ź�������Դ */
extern char WatchDogVector[ThreadNumTotal];

/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCSendInVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern SMsgQue *OSCRecInVector;

/* ʹ��һ����Ϣ�ڴ���Դ */
extern SDataSpace *DataSpace;



UINT WINAPI RTWork(void* pParam)
{
	unsigned int RTMsgIndexBuff = 0;
	
	// �߳�ѭ��
	while (!RTMThread->SExit)
	{
		/* ι�� */
		WatchDogVector[RTThreadNum] = TRUE;
		if (0 != RTInVector->Count)
		{
			RTMsgIndexBuff = RTInVector->PopFront();
			switch (DataSpace->MsgReadDest(RTMsgIndexBuff))
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* ����Ϣ��ַ���뷢���߳���� */
					OSCSendInVector->PushBack(RTMsgIndexBuff);
					break;
				case OSCRecThreadNum:
					/* ����Ϣ��ַ��������߳���� */
					OSCRecInVector->PushBack(RTMsgIndexBuff);
					break;
				default:break;
			}
		}
	}
	return 0;
}

