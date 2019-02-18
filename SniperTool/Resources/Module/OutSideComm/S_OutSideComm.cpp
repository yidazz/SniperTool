#include "S_OutSideComm.h"

/* 定义使用的协议分析器 */
ProtocolTable ProtocolSet = ProtocolFir;
/* 定义使用的外部交流器 */
OutSideCommTable OutSideCommSet = uSerialPort;

/** 发送监听函数*/
extern UINT WINAPI OSCSendThreadWork(void* pParam);
/** 接收监听线程函数*/
extern UINT WINAPI OSCRecThreadWork(void* pParam);

/* 使用两个线程资源 */
SThread *OSCSendThread = new SThread;
SThread *OSCRecThread = new SThread;

/* 使用一个外部交流器选择器资源 */
SOutSideCommSelect *OSCOutSideCommSelect = new SOutSideCommSelect;
/* 使用一个串口资源 */
SSerialPort *OSCSerialPort = new SSerialPort;

/* 使用一个帧分析器选择器资源 */
SByteAnalySelect *OSCByteAnalySelect = new SByteAnalySelect;
/* 使用一个帧分析器资源 */
SFirAnalysis *OSCFirAnalysis = new SFirAnalysis;

/* 使用一个业务发送器资源 */
SServiceSender *OSCServiceSender = new SServiceSender;

/* 使用一个业务发送队列缓存区资源 */
SVector *OSCSendBuffVector = new SVector;
/* 使用一个外部字节接收队列缓存区资源 */
SVector *OSCRecByteQueue = new SVector;
/* 使用一个数据队列缓存区资源 */
SVector *OSCDataBuffQueue = new SVector;
/* 使用一个等待数据被读取队列缓存区资源 */
SVector *OSCDataVector = new SVector;
/* 使用一个等待业务完成队列缓存区资源 */
SVector *OSCWaitBuffVector = new SVector;
/* 使用一个入口队列缓存区资源 */
SVector *OSCInBuffVector = new SVector;

/* 使用一个微秒定时器资源 */
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
	/** 是否有错误发生 */
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
	/** 初始化外部通信模块失败  关闭模块  并返回 */
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
	/** 关闭所有线程与串口 */
	OSCSendThread->EndThread();
	OSCRecThread->EndThread();

	return TRUE;
}

bool OutSideCommModule::OpenSerialPort()
{
	/** 是否有错误发生 */
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
