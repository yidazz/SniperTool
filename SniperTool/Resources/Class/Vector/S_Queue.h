#pragma once
#ifndef S_QUEUE_H
#define S_QUEUE_H  

#include <Windows.h>  
#include "Protocol.h"
using namespace std;

#define ErrUint      4294967295 // Uint���ֵ���������־
#define MsgQueLen    1000   //��Ϣ���г��� ���Ϊ 4294967294
#define DataSpaceLen 1000   //��Ϣ�����ڴ泤�� ���Ϊ 4294967294
//#define UintQueLen   1000   //��Ϣ�����ڴ泤�� ���Ϊ 4294967294

/** �Զ������� */

/* ��Ϣר�û��ζ����� */
class SMsgQue
{
public:
	SMsgQue();
	~SMsgQue();

public:
	bool PushBack(unsigned int Index);
	unsigned int PopFront();

public:
	unsigned int Count;  //���м��� 

private:
	unsigned int Que[MsgQueLen];

	unsigned int ReadIndex;
	unsigned int WriteIndex;
	CRITICAL_SECTION   csQue;   //�������һά����
};

/* ���������� */
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
//	unsigned int Count;  //���м��� 
//
//private:
//	unsigned int Que[UintQueLen];
//
//	unsigned int ReadIndex;
//	unsigned int WriteIndex;
//	CRITICAL_SECTION   csQue;   //�������һά����
//};


/* ��Ϣ�ڴ������ */
class SDataSpace
{
public:
	SDataSpace();
	~SDataSpace();

//�Կռ����
public:
	unsigned int UseSpace();         //����һ����Ϣ�ռ�   ���ؿռ�������
	bool SpaceDel(unsigned int Index);    //ɾ��һ����Ϣ�ռ�

//����Ϣ���ݲ���
public:
	bool MsgWrite(unsigned int Index, MsgStateProtocol MsgState,
		unsigned int DataCount, unsigned int ServiceNum,
		ThreadNum SourceNum, ThreadNum DestNum, char Data[MsgDataMaxLen]);

	MESSAGE MsgReadAll(unsigned int Index);
	ThreadNum MsgReadDest(unsigned int Index);
	char *MsgReadData(unsigned int Index);

public:
	unsigned int Count = 0;  //�ռ���� 

private:
	void SpaceMsgClear(unsigned int Index);

private:
	MESSAGE Space[DataSpaceLen];

	unsigned int PollIndex = 0; //��ѯָ��
	SpaceStateProtocol SpaceState[DataSpaceLen];   //����ڴ��Ƿ�ռ��
	CRITICAL_SECTION   csSpace;   //�������һά����
};





#endif //S_QUEUE_H 

