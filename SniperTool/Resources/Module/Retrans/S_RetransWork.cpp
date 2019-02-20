#include "S_RetransWork.h"

/* ʹ��һ��ҵ��������Դ */
extern SServiceSender *OSCServiceSender;
/* ʹ��һ���߳���Դ */
extern SThread *RTMThread;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *RTTimerUs;

/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csRTIn;   //������
/* ʹ��һ����ڶ��л�������Դ */
extern vector <MESSAGE*> RTInVector;

/* ʹ��һ�����Ź�������Դ */
extern SVector *WatchDogVector;

/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csOSCSendIn;   //������
/* ʹ��һ����ڶ��л�������Դ */
extern CRITICAL_SECTION S_csOSCRecIn;   //������
/* ʹ��һ��������ڶ��л�������Դ */
extern vector <MESSAGE*> OSCSendInBuffVector;
/* ʹ��һ��������ڶ��л�������Դ */
extern vector <MESSAGE*> OSCRecInBuffVector;



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
		if (a1 >= 2000)
		{
			printf("%d\n", a1);
		}
		RTTimerUs->Zero();
		/* ι�� */
		WatchDogVector->Queue1[RTThreadNum] = TRUE;
		/* �����ٽ�� */
		EnterCriticalSection(&S_csRTIn);
		if (NULL != RTInVector.size())
		{/*
			a1 += RTInVector.size();
			if (800 == ia1++)
			{
				printf("                 %d\n", (a1 / ia1));
				a1 = 0;
				ia1 = 0;
			}*/
			V = RTInVector[0];
			/* ����Ѿ�ת���ĵ�ַ */
			RTInVector.erase(RTInVector.begin());
			/** �뿪�ٽ�� */
			LeaveCriticalSection(&S_csRTIn);
			switch (V->DestNum)
			{
				case TWDThreadNum:
					break;
				case OSCSendThreadNum:
					/* �����ٽ�� */
					EnterCriticalSection(&S_csOSCSendIn);
					/* ����Ϣ��ַ����ת������� */
					OSCSendInBuffVector.push_back(V);
					/** �뿪�ٽ�� */
					LeaveCriticalSection(&S_csOSCSendIn);
					break;
				case OSCRecThreadNum:
					/* �����ٽ�� */
					EnterCriticalSection(&S_csOSCRecIn);
					/* ����Ϣ��ַ����ת������� */
					OSCRecInBuffVector.push_back(V);
					/** �뿪�ٽ�� */
					LeaveCriticalSection(&S_csOSCRecIn);
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
			//		EnterCriticalSection(&OSCSendInBuffVector->S_csVector2);
			//		OSCSendInBuffVector->Queue2.push_back(RTInVector[0]);
			//		RTInVector.erase(RTInVector.begin());
			//		/** �뿪�ٽ�� */
			//		LeaveCriticalSection(&OSCSendInBuffVector->S_csVector2);
			//		break;
			//	case OSCRecModNum:
			//		/** �����ٽ�� */
			//		EnterCriticalSection(&OSCRecInBuffVector->S_csVector2);
			//		OSCRecInBuffVector->Queue2.push_back(RTInVector->Queue2[0]);
			//		RTInVector->Queue2.erase(RTInVector->Queue2.begin());
			//		/** �뿪�ٽ�� */
			//		LeaveCriticalSection(&OSCRecInBuffVector->S_csVector2);
			//		break;
			//	default:break;
			//}
			/** �뿪�ٽ�� */
			//LeaveCriticalSection(&RTInVector->S_csVector2);
		}
		else
		{
			/** �뿪�ٽ�� */
			LeaveCriticalSection(&S_csRTIn);
		}
	}
	return 0;
}

