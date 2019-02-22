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

bool SMsgQue::PushBack(MESSAGE* Index)
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

MESSAGE* SMsgQue::PopFront()
{
	MESSAGE* Msg;
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
	return NULL;
}

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

MESSAGE* SDataSpace::UseSpace()
{
	MESSAGE* Index;
	/* �����ٽ�� */
	EnterCriticalSection(&csSpace);
	if (DataSpaceLen > Count)   //һ�����ҵ���λ
	{
		while (1)   //һ�����ҵ���λ
		{
			if (SpaceFree == SpaceState[PollIndex])
			{
				Space[PollIndex].MsgSpaPos = PollIndex;   //������Ϣ��Space�е�������
				Index = &Space[PollIndex];                //��ȡ�������ַ
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
	return NULL;
}

bool SDataSpace::SpaceDel(MESSAGE* Index)
{
	/* �����ٽ�� */
	EnterCriticalSection(&csSpace);
	if (SpaceFree == SpaceState[Index->MsgSpaPos])      //����ռ䱾�����ǿ���״̬  �򱨴�
	{
		/** �뿪�ٽ�� */
		LeaveCriticalSection(&csSpace);
		return FALSE;
	}
	SpaceState[Index->MsgSpaPos] = SpaceFree;         //���ռ���Ϊ����״̬
	SpaceMsgClear(Index);							//�ռ��ʼ��
	Count--;									

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&csSpace);
	return TRUE;
}

void SDataSpace::SpaceMsgClear(MESSAGE* Index)
{
	Index->MsgSpaPos = NULL;
	Index->MsgState = MsgUnHandle;
	Index->DataCount = 0;
	Index->ServiceNum = 0;
	Index->SourceNum = NoThreadNum;
	Index->DestNum = NoThreadNum;
	for (int i = 0;i < MsgDataMaxLen;i++)
	{
		Index->Data[i] = 0;
	}
}
