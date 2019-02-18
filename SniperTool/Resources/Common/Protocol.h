#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

/* �������� */

enum InsideProtocol {
	InServiceNum1,             // ҵ���ŵ�λ
	InServiceNum2,             // ҵ�����е�λ
	InServiceNum3,             // ҵ�����и�λ
	InServiceNum4,             // ҵ���Ÿ�λ
	InSource,                  // ��Դ��
	InDest,                    // Ŀ�ĺ�
	InsideProtocolTotal,       // ����
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
#endif //PROTOCOL_H_ 