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

bool SMsgQue::PushBack(unsigned int Index)
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

unsigned int SMsgQue::PopFront()
{
	unsigned int Msg;
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
	return ErrUint;
}

/**************************/
/*       环形数组类       */
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
//	/* 进入临界段 */
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
//		/** 离开临界段 */
//		LeaveCriticalSection(&csQue);
//		return TRUE;
//	}
//	/** 离开临界段 */
//	LeaveCriticalSection(&csQue);
//	return FALSE;
//}
//
//unsigned int SUintQue::PopFront()
//{
//	unsigned int Data;
//	/* 进入临界段 */
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
//		/** 离开临界段 */
//		LeaveCriticalSection(&csQue);
//		return Data;
//	}
//	/** 离开临界段 */
//	LeaveCriticalSection(&csQue);
//	return ErrUint;
//}

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

unsigned int SDataSpace::UseSpace()
{
	unsigned int Index;
	/* 进入临界段 */
	EnterCriticalSection(&csSpace);
	if (DataSpaceLen > Count)   //一定能找到空位
	{
		while (1)   //一定能找到空位
		{
			if (SpaceFree == SpaceState[PollIndex])
			{
				Index = PollIndex;   //取出消息在Space中的索引号
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
	return ErrUint;
}

bool SDataSpace::SpaceDel(unsigned int Index)
{
	/* 进入临界段 */
	EnterCriticalSection(&csSpace);
	if (SpaceFree == SpaceState[Index])      //如果空间本来就是空闲状态  则报错
	{
		/** 离开临界段 */
		LeaveCriticalSection(&csSpace);
		return FALSE;
	}
	SpaceState[Index] = SpaceFree;         //将空间置为空闲状态
	SpaceMsgClear(Index);							//空间初始化
	Count--;									

	/** 离开临界段 */
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
	// 子函数
	// 调用环境相关互斥量必须已上锁
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

