#include "S_Queue.h"  

/**************************/
/*   消息专用环形队列类   */
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
	/* 进入临界段 */
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
		/** 离开临界段 */
		LeaveCriticalSection(&csQue);
		return TRUE;
	}
	/** 离开临界段 */
	LeaveCriticalSection(&csQue);
	return FALSE;
}

MESSAGE* SMsgQue::PopFront()
{
	MESSAGE* Msg;
	/* 进入临界段 */
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
		/** 离开临界段 */
		LeaveCriticalSection(&csQue);
		return Msg;
	}
	/** 离开临界段 */
	LeaveCriticalSection(&csQue);
	return NULL;
}

/**************************/
/*     消息内存管理类     */
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
	/* 进入临界段 */
	EnterCriticalSection(&csSpace);
	if (DataSpaceLen > Count)   //一定能找到空位
	{
		while (1)   //一定能找到空位
		{
			if (SpaceFree == SpaceState[PollIndex])
			{
				Space[PollIndex].MsgSpaPos = PollIndex;   //存入消息在Space中的索引号
				Index = &Space[PollIndex];                //提取出这个地址
				SpaceState[PollIndex] = SpaceUsed;        //将空间占用标志置为占用状态
				PollIndex++;                              //找空位指针后移
				if (DataSpaceLen <= PollIndex)
				{
					PollIndex = NULL;
				}
				Count++;                     
				/** 离开临界段 */
				LeaveCriticalSection(&csSpace);
				return Index;					  		 //返回空位地址
			}
			else                                      //不是空位则指针后移   一定有空位
			{
				PollIndex++;
				if (DataSpaceLen <= PollIndex)
				{
					PollIndex = NULL;
				}
			}
		}
	}
	/** 离开临界段 */
	LeaveCriticalSection(&csSpace);
	return NULL;
}

bool SDataSpace::SpaceDel(MESSAGE* Index)
{
	/* 进入临界段 */
	EnterCriticalSection(&csSpace);
	if (SpaceFree == SpaceState[Index->MsgSpaPos])      //如果空间本来就是空闲状态  则报错
	{
		/** 离开临界段 */
		LeaveCriticalSection(&csSpace);
		return FALSE;
	}
	SpaceState[Index->MsgSpaPos] = SpaceFree;         //将空间置为空闲状态
	SpaceMsgClear(Index);							//空间初始化
	Count--;									

	/** 离开临界段 */
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
