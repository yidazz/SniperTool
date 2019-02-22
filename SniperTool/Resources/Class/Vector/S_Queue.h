#pragma once
#ifndef S_QUEUE_H
#define S_QUEUE_H  

#include <Windows.h>  
#include "Protocol.h"
using namespace std;

#define MsgQueLen 1000   //��Ϣ���г���
#define DataSpaceLen 1000   //��Ϣ�����ڴ泤��

/** �Զ������� */

/* ��Ϣר�û��ζ����� */
class SMsgQue
{
public:
	SMsgQue();
	~SMsgQue();

public:
	bool PushBack(MESSAGE* Index);
	MESSAGE* PopFront();

public:
	int Count;  //���м��� 

private:
	MESSAGE* Que[MsgQueLen];
	int ReadIndex;
	int WriteIndex;
	CRITICAL_SECTION   csQue;   //�������һά����
};


/* ��Ϣ�ڴ������ */
class SDataSpace
{
public:
	SDataSpace();
	~SDataSpace();

public:
	MESSAGE* UseSpace();
	bool SpaceDel(MESSAGE* Index);

public:
	int Count = 0;  //�ռ���� 

private:
	void SpaceMsgClear(MESSAGE* Index);

private:
	MESSAGE Space[DataSpaceLen];
	int PollIndex = 0; //��ѯָ��
	SpaceStateProtocol SpaceState[DataSpaceLen];   //����ڴ��Ƿ�ռ��
	CRITICAL_SECTION   csSpace;   //�������һά����
};





#endif //S_QUEUE_H 

