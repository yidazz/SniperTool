#include "S_ServiceSender.h"  

/* 使用一个业务发送队列缓存区资源 */
extern SVector *OSCSendBuffVector;
/* 使用一个外部字节接收队列缓存区资源 */
extern SVector *OSCRecByteQueue;
/* 使用一个发送入口队列缓存区资源 */
extern SVector *OSCSendInBuffVector;
/* 使用一个接收入口队列缓存区资源 */
extern SVector *OSCRecInBuffVector;
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


bool SServiceSender::ServiceSender()
{
	while (NULL != OSCSendBuffVector->Queue2.size())
	{
		int len = OSCSendBuffVector->Queue2[0].size();
		MESSAGE *Que = new MESSAGE;
		Que->Data.swap(OSCSendBuffVector->Queue2[0]);
		OSCSendBuffVector->Queue2.erase(OSCSendBuffVector->Queue2.begin());
		Que->ServiceNum = -1;
		RTInVector.push_back(Que);
	}





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

	return TRUE;
}
