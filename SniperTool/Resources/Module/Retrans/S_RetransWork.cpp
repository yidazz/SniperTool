#include "S_RetransWork.h"

/* ʹ��һ���߳���Դ */
extern SThread *RTMThread;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *RTTimerUs;

/* ʹ��һ����ڶ��л�������Դ */
extern SVector *RTInVector;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;

/* ʹ��һ��������ڶ��л�������Դ */
extern SVector *OSCSendInBuffVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern SVector *OSCRecInBuffVector;

UINT WINAPI RTWork(void* pParam)
{
	// �߳�ѭ��
	while (!RTMThread->SExit)
	{
		/* ι�� */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;

		if (NULL != RTInVector->Queue2.size())
		{
			/** �����ٽ�� */
			EnterCriticalSection(&RTInVector->S_csVector2);

			switch (RTInVector->Queue2[0][InDest])
			{
				case OSCSendModNum: 
					/** �����ٽ�� */
					EnterCriticalSection(&OSCSendInBuffVector->S_csVector2);
					OSCSendInBuffVector->Queue2.push_back(RTInVector->Queue2[0]);
					RTInVector->Queue2.erase(RTInVector->Queue2.begin());
					/** �뿪�ٽ�� */
					LeaveCriticalSection(&OSCSendInBuffVector->S_csVector2);
					break;
				case OSCRecModNum:
					/** �����ٽ�� */
					EnterCriticalSection(&OSCRecInBuffVector->S_csVector2);
					OSCRecInBuffVector->Queue2.push_back(RTInVector->Queue2[0]);
					RTInVector->Queue2.erase(RTInVector->Queue2.begin());
					/** �뿪�ٽ�� */
					LeaveCriticalSection(&OSCRecInBuffVector->S_csVector2);
					break;
				default:break;
			}
			/** �뿪�ٽ�� */
			LeaveCriticalSection(&RTInVector->S_csVector2);
		}
	}
	return 0;
}

