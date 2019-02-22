#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

#include <Windows.h>  

/* �������� */

#define MsgDataMaxLen 1000   //




enum ServiceMsgProtocol {
	ServiceNum1,              // ҵ���ŵ�λ
	ServiceNum2,              // ҵ�����е�λ
	ServiceNum3,              // ҵ�����и�λ
	ServiceNum4,              // ҵ���Ÿ�λ
	ServiceSourceNum,                  // ��Դ��
	ServiceDestNum,                    // Ŀ�ĺ�
	ServiceMsgProtocolTotal,        // ����
	/* ʣ���ֽڸ�ʽ���ո�ģ��ҵ���Ҫ��ĸ�ʽ���� */
};

enum ThreadNum {
	NoThreadNum,          //Ԥ��
	TWDThreadNum,             //�߳̿��Ź��߳�
	RTThreadNum,              //ת�����߳�
	OSCSendThreadNum,         //�����߳�
	OSCRecThreadNum,          //�����߳�
	ThreadNumTotal,       // ����
};

enum ModuleNum {
	NoModNum,             // ��ģ��
	TWDModNum,             // �߳̿��Ź�ģ��
	RTModNum,             // ת����ģ��
	OSCSendModNum,            // �ⲿ������ģ��
	OSCRecModNum,          // �ⲿ������ģ��
	ModuleNumTotal,       // ����
};

enum InBuffMsgProtocol {
	InSource,                  // ��Դ��
	InDest,                    // Ŀ�ĺ�
	InIndex,                   // ��Ϣ����
	InBuffMsgProtocolTotal,       // ����
};

enum MsgStateProtocol {
	MsgUnHandle,                 // δ����
	MsgHandling,                 // ������
	MsgHadHandle,                // �Ѵ���
	MsgStateProtocolTotal,      // ����
};
enum SpaceStateProtocol {
	SpaceFree,                // �ռ���� 
	SpaceUsed,                 // �ռ�ռ��
	SpaceStateProtocolTotal,      // ����
};

/* ��Ϣ�ṹ�� */
typedef struct
{
	/* �ṹ��״̬ */
	unsigned int  MsgSpaPos = NULL;  //��Ϣ�ڿռ��е�λ��
	MsgStateProtocol MsgState = MsgUnHandle; //��Ϣ״̬
	int DataCount = 0;   //���ݸ���
	/* �ṹ������ */
	unsigned int ServiceNum = 0;  //��Ϣ���
	ThreadNum SourceNum = NoThreadNum;//��Դģ��
	ThreadNum DestNum = NoThreadNum;//Ŀ��ģ��
	char Data[MsgDataMaxLen] = { 0 }; //����
}MESSAGE;


#endif