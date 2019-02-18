#include "S_ServiceSender.h"  

/* 使用一个业务发送队列缓存区资源 */
extern SVector *OSCSendBuffVector;
/* 使用一个外部字节接收队列缓存区资源 */
extern SVector *OSCRecByteQueue;
/* 使用一个数据队列缓存区资源 */
extern SVector *OSCDataBuffQueue;
/* 使用一个等待数据被读取队列缓存区资源 */
extern SVector *OSCDataVector;
/* 使用一个等待业务完成队列缓存区资源 */
extern SVector *OSCWaitBuffVector;
/* 使用一个入口队列缓存区资源 */
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
