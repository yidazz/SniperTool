#include "S_OutSideComm.h"

/* ����ʹ�õ�Э������� */
ProtocolTable ProtocolSet = ProtocolFir;
/* ����ʹ�õ��ⲿ������ */
OutSideCommTable OutSideCommSet = uSerialPort;

/** ���ͼ�������*/
extern UINT WINAPI OSCSendThreadWork(void* pParam);
/** ���ռ����̺߳���*/
extern UINT WINAPI OSCRecThreadWork(void* pParam);

/* ʹ�������߳���Դ */
SThread *OSCSendThread = new SThread;
SThread *OSCRecThread = new SThread;

/* ʹ��һ���ⲿ������ѡ������Դ */
SOutSideCommSelect *OSCOutSideCommSelect = new SOutSideCommSelect;
/* ʹ��һ��������Դ */
SSerialPort *OSCSerialPort = new SSerialPort;

/* ʹ��һ��֡������ѡ������Դ */
SByteAnalySelect *OSCByteAnalySelect = new SByteAnalySelect;
/* ʹ��һ��֡��������Դ */
SFirAnalysis *OSCFirAnalysis = new SFirAnalysis;

/* ʹ��һ��ҵ��������Դ */
SServiceSender *OSCServiceSender = new SServiceSender;

/* ʹ��һ��ҵ���Ͷ��л�������Դ */
SVector *OSCSendBuffVector = new SVector;
/* ʹ��һ���ⲿ�ֽڽ��ն��л�������Դ */
SVector *OSCRecByteQueue = new SVector;
/* ʹ��һ�����ݶ��л�������Դ */
SVector *OSCDataBuffQueue = new SVector;
/* ʹ��һ���ȴ����ݱ���ȡ���л�������Դ */
SVector *OSCDataVector = new SVector;
/* ʹ��һ���ȴ�ҵ����ɶ��л�������Դ */
SVector *OSCWaitBuffVector = new SVector;
/* ʹ��һ����ڶ��л�������Դ */
SVector *OSCInBuffVector = new SVector;

/* ʹ��һ��΢�붨ʱ����Դ */
STimerUs *OSCTimerUs = new STimerUs;


OutSideCommModule::OutSideCommModule()
{
	ErrCode = NoError;
}

OutSideCommModule::~OutSideCommModule()
{
	ErrCode = NoError;
	EndOSCM();
	CloseSerialPort();
}

bool OutSideCommModule::InitOSCM()
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;
	ErrCode = NoError;

	if (bIsSuccess)
	{
		bIsSuccess = OSCSendThread->CreateThread(OSCSendThreadWork);
		if (bIsSuccess)
		{
			bIsSuccess = OSCRecThread->CreateThread(OSCRecThreadWork);
			if (!bIsSuccess)
			{
				if (NoError != ErrCode) { ErrCode = OSCM_CreateRecThread; }
			}
		}
		else
		{
			if (NoError != ErrCode) { ErrCode = OSCM_CreateSendThread; }
		}
	}
	/** ��ʼ���ⲿͨ��ģ��ʧ��  �ر�ģ��  ������ */
	if (!bIsSuccess)
	{
		OSCSendThread->EndThread();
		OSCRecThread->EndThread();
		return FALSE;
	}
	return TRUE;
}

bool OutSideCommModule::EndOSCM()
{
	/** �ر������߳��봮�� */
	OSCSendThread->EndThread();
	OSCRecThread->EndThread();

	return TRUE;
}

bool OutSideCommModule::OpenSerialPort()
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;
	ErrCode = NoError;

	if (bIsSuccess)
	{
		bIsSuccess = OSCSerialPort->InitPort();
	}
	if (!bIsSuccess)
	{
		if (NoError != ErrCode) { ErrCode = SerialPort_InitPort; }
		return FALSE;
	}
	return TRUE;
}

bool OutSideCommModule::CloseSerialPort()
{
	OSCSerialPort->ClosePort();
	return TRUE;
}
