#pragma once
#ifndef S_BYTEANALYSIS_H_  
#define S_BYTEANALYSIS_H_  

#include <Windows.h>  
#include <qDebug.h>  
#include "QueueConfig.h"
#include "S_Queue.h"
#include "S_ByteAnalySelect.h"
#include "Protocol.h"
#include "S_ServiceSender.h"  
#include "S_TimerUs.h"  


class SFirAnalysis
{
public:
	SFirAnalysis();
	~SFirAnalysis();

public:
	/** FLP ֡������ */
	bool FirAnalysis(char &rRecByte);

private:
	bool FirConfirm(void);

};


//class SSecAnalysis
//{
//public:
//	SSecAnalysis();
//	~SSecAnalysis();
//
//public:
//	/** ֡������ */
//	bool SecAnalysis(char &rRecByte);
//
//private:
//	SVector *RecByteQueue;
//
//};

enum FrameState {
	NoComplete,               //֡δ����
	FramePerfect,             //�յ�����֡
	FrameError,         //�յ�������֡
	FrameStateTotal,       // ����
};


#endif //S_BYTEANALYSIS_H_ 
