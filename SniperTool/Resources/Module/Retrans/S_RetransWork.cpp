#include "S_RetransWork.h"

/* ʹ��һ���߳���Դ */
extern SThread *RTMThread;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *RTTimerUs;

/* ʹ��һ����ڶ��л�������Դ */
extern SVector *RTInVector;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;


UINT WINAPI RTWork(void* pParam)
{
	// �߳�ѭ��
	while (!RTMThread->SExit)
	{
		/* ι�� */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;

		if (NULL != RTInVector->Queue2.size())
		{
			switch (RTInVector->Queue2[0][InDest])
			{
				case OSCSendModNum: break;
				case OSCRecModNum: break;
				default:break;
			}
		}
	}
	return 0;
}

