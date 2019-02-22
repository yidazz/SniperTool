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



UINT WINAPI RTWork(void* pParam)
{
	MESSAGE *V;
	uint a1 = 0;
	int ia1 = 0;
	RTTimerUs->Zero();
	// �߳�ѭ��
	while (!RTMThread->SExit)
	{
		a1 = RTTimerUs->Timer();
		if (a1 >= 1000 && ++ia1 == 1)
		{
			printf("%d\n", (a1 / ia1));
			a1 = 0;
			ia1 = 0;
		}
		RTTimerUs->Zero();
		/* ι�� */
		WatchDogVector[RTThreadNum] = TRUE;
		if (0 != RTInVector->Count)
		{/*
			a1 += RTInVector.size();
			if (800 == ia1++)
			{
				printf("                 %d\n", (a1 / ia1));
				a1 = 0;
				ia1 = 0;
			}*/
			V = RTInVector->PopFront();
			switch (V->DestNum)
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* ����Ϣ��ַ����ת������� */
					OSCSendInVector->PushBack(V);
					break;
				case OSCRecThreadNum:
					/* ����Ϣ��ַ����ת������� */
					OSCRecInVector->PushBack(V);
					break;
				default:break;
			}

			//system("cls");
			//printf("1:%d \n",RTInVector[0]);
			//V = RTInVector[0];
			//printf("2: ");
			//	
			//for (UINT i = 0; i < V->Data.size(); i++)
			//{
			//	printf("%X ", V->Data[i]);
			//}
			//printf("\n");
			//delete V;
			//RTInVector.erase(RTInVector.begin());

			/** �����ٽ�� */
			//EnterCriticalSection(&RTInVector->S_csVector2);

			//switch (RTInVecto[0])
			//{
			//	case OSCSendModNum: 
			//		/** �����ٽ�� */
			//		EnterCriticalSection(&OSCSendInVector->S_csVector2);
			//		OSCSendInVector->Queue2.push_back(RTInVector[0]);
			//		RTInVector.erase(RTInVector.begin());
			//		/** �뿪�ٽ�� */
			//		LeaveCriticalSection(&OSCSendInVector->S_csVector2);
			//		break;
			//	case OSCRecModNum:
			//		/** �����ٽ�� */
			//		EnterCriticalSection(&OSCRecInVector->S_csVector2);
			//		OSCRecInVector->Queue2.push_back(RTInVector->Queue2[0]);
			//		RTInVector->Queue2.erase(RTInVector->Queue2.begin());
			//		/** �뿪�ٽ�� */
			//		LeaveCriticalSection(&OSCRecInVector->S_csVector2);
			//		break;
			//	default:break;
			//}
			/** �뿪�ٽ�� */
			//LeaveCriticalSection(&RTInVector->S_csVector2);
		}
	}
	return 0;
}

