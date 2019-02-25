#pragma once
#ifndef S_QUEUE_H
#define S_QUEUE_H  

#include <Windows.h>  
#include "Protocol.h"
using namespace std;

#define ErrUint      4294967295 // Uint最大值用作错误标志
#define MsgQueLen    1000   //消息队列长度 最大为 4294967294
#define DataSpaceLen 1000   //消息数据内存长度 最大为 4294967294
//#define UintQueLen   1000   //消息数据内存长度 最大为 4294967294

/** 自定队列类 */

/* 消息专用环形队列类 */
class SMsgQue
{
public:
	SMsgQue();
	~SMsgQue();

public:
	bool PushBack(unsigned int Index);
	unsigned int PopFront();

public:
	unsigned int Count;  //队列计数 

private:
	unsigned int Que[MsgQueLen];

	unsigned int ReadIndex;
	unsigned int WriteIndex;
	CRITICAL_SECTION   csQue;   //互斥操作一维队列
};

/* 环形数组类 */
//class SUintQue
//{
//public:
//	SUintQue();
//	~SUintQue();
//
//public:
//	bool PushBack(unsigned int Data);
//	unsigned int PopFront();
//
//public:
//	unsigned int Count;  //队列计数 
//
//private:
//	unsigned int Que[UintQueLen];
//
//	unsigned int ReadIndex;
//	unsigned int WriteIndex;
//	CRITICAL_SECTION   csQue;   //互斥操作一维队列
//};


/* 消息内存管理类 */
class SDataSpace
{
public:
	SDataSpace();
	~SDataSpace();

//对空间操作
public:
	unsigned int UseSpace();         //申请一个消息空间   返回空间索引号
	bool SpaceDel(unsigned int Index);    //删除一个消息空间

//对消息内容操作
public:
	bool MsgWrite(unsigned int Index, MsgStateProtocol MsgState,
		unsigned int DataCount, unsigned int ServiceNum,
		ThreadNum SourceNum, ThreadNum DestNum, char Data[MsgDataMaxLen]);

	MESSAGE MsgReadAll(unsigned int Index);
	ThreadNum MsgReadDest(unsigned int Index);
	char *MsgReadData(unsigned int Index);

public:
	unsigned int Count = 0;  //空间计数 

private:
	void SpaceMsgClear(unsigned int Index);

private:
	MESSAGE Space[DataSpaceLen];

	unsigned int PollIndex = 0; //轮询指针
	SpaceStateProtocol SpaceState[DataSpaceLen];   //标记内存是否被占用
	CRITICAL_SECTION   csSpace;   //互斥操作一维队列
};





#endif //S_QUEUE_H 

