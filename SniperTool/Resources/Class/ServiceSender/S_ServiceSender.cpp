#include "S_ServiceSender.h"  

/* 使用一个业务发送队列缓存区资源 */
extern SVector *OSCSendBuffVector;
/* 使用一个外部字节接收队列缓存区资源 */
extern SVector *OSCRecByteQueue;
/* 使用一个发送入口队列缓存区资源 */
extern SVector *OSCSendInBuffVector;
/* 使用一个接收入口队列缓存区资源 */
extern SVector *OSCRecInBuffVector;
/* 使用一个入口队列互斥量资源 */
extern CRITICAL_SECTION S_csRTIn;   //互斥量
/* 使用一个入口队列缓存区资源 */
extern vector <MESSAGE*> RTInVector;

int lastsize1 = 0;
int lastsize2 = 0;
int lastsize3 = 0;

SServiceSender::SServiceSender()
{
}

SServiceSender::~SServiceSender()
{
}


bool SServiceSender::ServiceSender(MESSAGE* MessageIndex)
{
	/* 进入临界段 */
	EnterCriticalSection(&S_csRTIn);
	/* 将消息地址推入转发器入口 */
	RTInVector.push_back(MessageIndex);
	/** 离开临界段 */
	LeaveCriticalSection(&S_csRTIn);
	return TRUE;

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


	//system("cls");
	//cout << " 1:  ";
	//for (UINT i = 0; i < OSCRecByteQueue->Queue1.size(); i++)
	//{
	//	cout << hex << (unsigned int)(unsigned char)(OSCRecByteQueue->Queue1[i]) << " ";
	//}
	//cout << endl;
	//cout << endl;

	//cout << " 2:  ";
	//for (UINT i = 0; i < OSCRecByteQueue->Queue2.size(); i++)
	//{
	//	for (UINT j = 0; j < OSCRecByteQueue->Queue2[i].size(); j++)
	//	{
	//		cout << hex << (unsigned int)(unsigned char)(OSCRecByteQueue->Queue2[i][j]) << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << endl;

}
