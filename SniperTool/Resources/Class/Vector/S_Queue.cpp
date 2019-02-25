#include "S_Queue.h"  

/**************************/
/*   ��Ϣר�û��ζ�����   */
/**************************/


SMsgQue::SMsgQue()
{
	ReadIndex = NULL;
	WriteIndex = NULL;
	Count = NULL;
	InitializeCriticalSection(&csQue);
}

SMsgQue::~SMsgQue()
{
	DeleteCriticalSection(&csQue);
}

bool SMsgQue::PushBack(unsigned int Index)
{
	/* �����ٽ�� */
	EnterCriticalSection(&csQue);
	if (MsgQueLen > Count)
	{
		Que[WriteIndex] = Index;
		WriteIndex++;
		if (MsgQueLen <= WriteIndex)
		{
			WriteIndex = NULL;
		}
		Count++;
		/** �뿪�ٽ�� */
		LeaveCriticalSection(&csQue);
		return TRUE;
	}
	/** �뿪�ٽ�� */
	LeaveCriticalSection(&csQue);
	return FALSE;
}

unsigned int SMsgQue::PopFront()
{
	unsigned int Msg;
	/* �����ٽ�� */
	EnterCriticalSection(&csQue);
	if (0 != Count)
	{
		Msg = Que[ReadIndex];
		ReadIndex++;
		if (MsgQueLen <= ReadIndex)
		{
			ReadIndex = NULL;
		}
		Count--;
		/** �뿪�ٽ�� */
		LeaveCriticalSection(&csQue);
		return Msg;
	}
	/** �뿪�ٽ�� */
	LeaveCriticalSection(&csQue);
	return ErrUint;
}

/**************************/
/*       ����������       */
/**************************/
//
//
//SUintQue::SUintQue()
//{
//	ReadIndex = NULL;
//	WriteIndex = NULL;
//	Count = NULL;
//	InitializeCriticalSection(&csQue);
//}
//
//SUintQue::~SUintQue()
//{
//	DeleteCriticalSection(&csQue);
//}
//
//bool SUintQue::PushBack(unsigned int Data)
//{
//	/* �����ٽ�� */
//	EnterCriticalSection(&csQue);
//	if (MsgQueLen > Count)
//	{
//		Que[WriteIndex] = Data;
//		WriteIndex++;
//		if (MsgQueLen <= WriteIndex)
//		{
//			WriteIndex = NULL;
//		}
//		Count++;
//		/** �뿪�ٽ�� */
//		LeaveCriticalSection(&csQue);
//		return TRUE;
//	}
//	/** �뿪�ٽ�� */
//	LeaveCriticalSection(&csQue);
//	return FALSE;
//}
//
//unsigned int SUintQue::PopFront()
//{
//	unsigned int Data;
//	/* �����ٽ�� */
//	EnterCriticalSection(&csQue);
//	if (0 != Count)
//	{
//		Data = Que[ReadIndex];
//		ReadIndex++;
//		if (MsgQueLen <= ReadIndex)
//		{
//			ReadIndex = NULL;
//		}
//		Count--;
//		/** �뿪�ٽ�� */
//		LeaveCriticalSection(&csQue);
//		return Data;
//	}
//	/** �뿪�ٽ�� */
//	LeaveCriticalSection(&csQue);
//	return ErrUint;
//}

/**************************/
/*     ��Ϣ�ڴ������     */
/**************************/

SDataSpace::SDataSpace()
{
	for (int i = 0;i < DataSpaceLen;i++)
	{
		SpaceState[i] = SpaceFree;
	}
	PollIndex = NULL;
	Count = NULL;
	InitializeCriticalSection(&csSpace);
}

SDataSpace::~SDataSpace()
{
	DeleteCriticalSection(&csSpace);
}

unsigned int SDataSpace::UseSpace()
{
	unsigned int Index;
	/* �����ٽ�� */
	EnterCriticalSection(&csSpace);
	if (DataSpaceLen > Count)   //һ�����ҵ���λ
	{
		while (1)   //һ�����ҵ���λ
		{
			if (SpaceFree == SpaceState[PollIndex])
			{
				Index = PollIndex;   //ȡ����Ϣ��Space�е�������
				SpaceState[PollIndex] = SpaceUsed;        //���ռ�ռ�ñ�־��Ϊռ��״̬
				PollIndex++;                              //�ҿ�λָ�����
				if (DataSpaceLen <= PollIndex)
				{
					PollIndex = NULL;
				}
				Count++;                     
				/** �뿪�ٽ�� */
				LeaveCriticalSection(&csSpace);
				return Index;					  		 //���ؿ�λ��ַ
			}
			else                                      //���ǿ�λ��ָ�����   һ���п�λ
			{
				PollIndex++;
				if (DataSpaceLen <= PollIndex)
				{
					PollIndex = NULL;
				}
			}
		}
	}
	/** �뿪�ٽ�� */
	LeaveCriticalSection(&csSpace);
	return ErrUint;
}

bool SDataSpace::SpaceDel(unsigned int Index)
{
	/* �����ٽ�� */
	EnterCriticalSection(&csSpace);
	if (SpaceFree == SpaceState[Index])      //����ռ䱾�����ǿ���״̬  �򱨴�
	{
		/** �뿪�ٽ�� */
		LeaveCriticalSection(&csSpace);
		return FALSE;
	}
	SpaceState[Index] = SpaceFree;         //���ռ���Ϊ����״̬
	SpaceMsgClear(Index);							//�ռ��ʼ��
	Count--;									

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&csSpace);
	return TRUE;
}

bool SDataSpace::MsgWrite(unsigned int Index, MsgStateProtocol MsgState,
	unsigned int DataCount, unsigned int ServiceNum,
	ThreadNum SourceNum, ThreadNum DestNum, char Data[MsgDataMaxLen])
{
	Space[Index].MsgState = MsgState;
	Space[Index].DataCount = DataCount;
	Space[Index].ServiceNum = ServiceNum;
	Space[Index].SourceNum = SourceNum;
	Space[Index].DestNum = DestNum;
	for (int i = 0; i < Space[Index].DataCount; i++)
	{
		Space[Index].Data[i] = Data[i];
	}
	return TRUE;
}

MESSAGE SDataSpace::MsgReadAll(unsigned int Index)
{
	return Space[Index];
}

ThreadNum SDataSpace::MsgReadDest(unsigned int Index)
{
	return Space[Index].DestNum;
}

char* SDataSpace::MsgReadData(unsigned int Index)
{
	return &Space[Index].Data[0];
}

void SDataSpace::SpaceMsgClear(unsigned int Index)
{
	// �Ӻ���
	// ���û�����ػ���������������
	Space[Index].MsgState = NoMsgState;
	Space[Index].DataCount = 0;
	Space[Index].ServiceNum = 0;
	Space[Index].SourceNum = NoThreadNum;
	Space[Index].DestNum = NoThreadNum;
	for (int i = 0;i < MsgDataMaxLen;i++)
	{
		Space[Index].Data[i] = 0;
	}
}

