#pragma once
#ifndef S_QUEUE_H
#define S_QUEUE_H  

#include <Windows.h>  
#include "Protocol.h"
using namespace std;

#define MsgQueLen 1000   //消息队列长度
#define DataSpaceLen 1000   //消息数据内存长度

/** 自定队列类 */

/* 消息专用环形队列类 */
class SMsgQue
{
public:
	SMsgQue();
	~SMsgQue();

public:
	bool PushBack(MESSAGE* Index);
	MESSAGE* PopFront();

public:
	int Count;  //队列计数 

private:
	MESSAGE* Que[MsgQueLen];
	int ReadIndex;
	int WriteIndex;
	CRITICAL_SECTION   csQue;   //互斥操作一维队列
};


/* 消息内存管理类 */
class SDataSpace
{
public:
	SDataSpace();
	~SDataSpace();

public:
	MESSAGE* UseSpace();
	bool SpaceDel(MESSAGE* Index);

public:
	int Count = 0;  //空间计数 

private:
	void SpaceMsgClear(MESSAGE* Index);

private:
	MESSAGE Space[DataSpaceLen];
	int PollIndex = 0; //轮询指针
	SpaceStateProtocol SpaceState[DataSpaceLen];   //标记内存是否被占用
	CRITICAL_SECTION   csSpace;   //互斥操作一维队列
};





#endif //S_QUEUE_H 

