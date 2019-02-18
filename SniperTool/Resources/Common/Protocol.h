#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

/* �������� */

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

#endif //PROTOCOL_H_ 