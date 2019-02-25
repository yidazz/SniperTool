#include "S_ByteAnalysis.h"

/* ʹ��һ��ҵ��������Դ */
extern SServiceSender *OSCServiceSender;

/* ʹ��һ���ⲿ�ֽڽ��ն��л�������Դ */
//extern SVector *OSCRecByteQueue;

/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCSendTimerUs;
/* ʹ��һ��΢�붨ʱ����Դ */
extern STimerUs *OSCRecTimerUs;

/* ʹ��һ����Ϣ�ڴ���Դ */
extern SDataSpace *DataSpace;
/* ʹ��һ����ʱ�����ö�ʱ����Դ */
STimerUs *Temp1 =new STimerUs;
STimerUs *Temp2 = new STimerUs;
STimerUs *Temp3 = new STimerUs;

uint Sa1 = 0;
uint Sa2 = 0;
int temp = 0;

void TempMakeMsg(MESSAGE* Message)
{
	for (int i = 0;i < 100;i++)
	{
		Message->Data[i] = 3;
	}
	Message->DestNum = OSCSendThreadNum;
}

SFirAnalysis::SFirAnalysis()
{
}

SFirAnalysis::~SFirAnalysis()
{
}

bool SFirAnalysis::FirAnalysis(char &rRecByte)
{
	unsigned int NewMemory;
	char TempData[1] = { 1 };
	/** �յ�֡�Ŀ�ͷ */
	//if (ProFir_Header == rRecByte)
	//{
	//	/** �жϻ��������Ƿ��в�ȱ���� */
	//	if (NULL != OSCRecByteQueue->Queue1.size())
	//	{
	//		/* �в�ȱ���� �򿽱������ݶ��л����� */
	//		OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
	//		/* �����ʱ������ */
	//		OSCRecByteQueue->Queue1.clear();
	//		/* �������ݴ�����ʱ������ */
	//		OSCRecByteQueue->Queue1.push_back(rRecByte);
	//		/* �յ��������� */
	//		State = FrameError;
	//	}
	//	else
	//	{
	//		/* �������ݴ�����ʱ������ */
	//		OSCRecByteQueue->Queue1.push_back(rRecByte);
	//	}
	//}
	///** �յ�֡�Ľ�β */
	//else if (ProFir_End == rRecByte)
	//{
	//	/* �������ݴ�����ʱ������ */
	//	OSCRecByteQueue->Queue1.push_back(rRecByte);
	//	/* �ж�֡�Ƿ��������� */
	//	if(TRUE!= FirConfirm())
	//	{
	//		/* �յ��������� */
	//		State = FrameError;
	//	}
	//	else
	//	{
	//		/* �յ��������� */
	//		State = FramePerfect;
	//	}
	//	/* ����֡���������������� */
	//	OSCRecByteQueue->Queue2.push_back(OSCRecByteQueue->Queue1);
	//	/* �����ʱ������ */
	//	OSCRecByteQueue->Queue1.clear();

	//}
	//else
	//{
	//	/* �������ݴ�����ʱ������ */
	//	OSCRecByteQueue->Queue1.push_back(rRecByte);
	//}
	//Sa1 = Temp1->Timer();
	//if (Sa1 >= 2000)
	//{
	//	printf("D      %d\n", Sa1);
	//}
	//if (NoComplete != State)
	{
		/* ����һ���ڴ��� */
		NewMemory = DataSpace->UseSpace();
		if (ErrUint != NewMemory)
		{
			/* ��װҵ��������Ϣ */
			DataSpace->MsgWrite(NewMemory, MsgUnHandle, 1, 0, OSCRecThreadNum, OSCSendThreadNum, TempData);
			/* �����ڴ�����ַ */
			OSCServiceSender->ServiceSender(NewMemory);
		}
	}
	return TRUE;
}


bool SFirAnalysis::FirConfirm(void)
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	///* �Ƿ���ڵ���4���ֽ�*/
	//if (bIsSuccess)
	//{
	//	if (4 > OSCRecByteQueue->Queue1.size()) {
	//		bIsSuccess = FALSE; }
	//}
	///* �Ƿ�Ϊָ��֡ͷ*/
	//if (bIsSuccess)
	//{
	//	if (ProFir_Header != OSCRecByteQueue->Queue1[0]) {
	//		bIsSuccess = FALSE; }
	//}
	///* �Ƿ�Ϊָ��֡β*/
	//if (bIsSuccess)
	//{
	//	if (ProFir_End != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 1]) {
	//		bIsSuccess = FALSE; }
	//}
	///* У����Ƿ���ȷ*/
	//if (bIsSuccess)
	//{
	//	char CheckBuff = 0;

	//	for (UINT i = 0; i < OSCRecByteQueue->Queue1.size() - 2; i++)
	//	{
	//		CheckBuff += OSCRecByteQueue->Queue1[i];
	//	}
	//	if (CheckBuff != OSCRecByteQueue->Queue1[OSCRecByteQueue->Queue1.size() - 2]) {
	//		bIsSuccess = FALSE; }
	//}

	return (TRUE == bIsSuccess);
}