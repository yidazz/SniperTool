#include "S_ServiceSender.h"  

/* ʹ��һ��ҵ���Ͷ��л�������Դ */
extern SVector *OSCSendBuffVector;
/* ʹ��һ���ⲿ�ֽڽ��ն��л�������Դ */
extern SVector *OSCRecByteQueue;
/* ʹ��һ�����ݶ��л�������Դ */
extern SVector *OSCDataBuffQueue;
/* ʹ��һ���ȴ����ݱ���ȡ���л�������Դ */
extern SVector *OSCDataVector;
/* ʹ��һ���ȴ�ҵ����ɶ��л�������Դ */
extern SVector *OSCWaitBuffVector;
/* ʹ��һ����ڶ��л�������Դ */
extern SVector *OSCInBuffVector;

int lastsize1 = 0;
int lastsize2 = 0;
int lastsize3 = 0;

SServiceSender::SServiceSender()
{
}

SServiceSender::~SServiceSender()
{
}


bool SServiceSender::ServiceSender()
{
	//if (0 != OSCSendBuffVector->Queue2.size() && lastsize1 != OSCSendBuffVector->Queue2.size())
	//{
	//	lastsize1 = OSCSendBuffVector->Queue2.size();
	//	for (UINT i = 0; i < OSCSendBuffVector->Queue2.size(); i++)
	//	{
	//		cout << " OSCSendBuffVector:  ";
	//		for (UINT j = 0; j < OSCSendBuffVector->Queue2[i].size(); j++)
	//		{
	//			cout << hex << (unsigned int)(unsigned char)(OSCSendBuffVector->Queue2[i][j]) << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}


	system("cls");
	cout << " 1:  ";
	for (UINT i = 0; i < OSCRecByteQueue->Queue1.size(); i++)
	{
		cout << hex << (unsigned int)(unsigned char)(OSCRecByteQueue->Queue1[i]) << " ";
	}
	cout << endl;
	cout << endl;

	cout << " 2:  ";
	for (UINT i = 0; i < OSCDataBuffQueue->Queue2.size(); i++)
	{
		for (UINT j = 0; j < OSCDataBuffQueue->Queue2[i].size(); j++)
		{
			cout << hex << (unsigned int)(unsigned char)(OSCDataBuffQueue->Queue2[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	//if (0 == ServiceSendQueue->Queue2.size())
	//{
	//	return FALSE;
	//}
	return TRUE;
}
