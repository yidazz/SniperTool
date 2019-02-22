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
	/** FLP 帧分析器 */
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
//	/** 帧分析器 */
//	bool SecAnalysis(char &rRecByte);
//
//private:
//	SVector *RecByteQueue;
//
//};

enum FrameState {
	NoComplete,               //帧未收完
	FramePerfect,             //收到完整帧
	FrameError,         //收到不完整帧
	FrameStateTotal,       // 总数
};


#endif //S_BYTEANALYSIS_H_ 
