#pragma once
#ifndef S_RETRANS_H_  
#define S_RETRANS_H_  

#include <Windows.h>  
#include "ErrorTable.h"
#include "S_SerialPort.h"  
#include "S_Thread.h"
#include "S_ByteAnalysis.h"
#include "S_TimerUs.h"  
#include "S_OutSideCommSelect.h"
#include "S_ByteAnalySelect.h"
#include "S_ServiceSender.h"  
#include "S_Queue.h"  

/** 转发器模块类
*
*  本类实现了转发器模块的基本功能
*
*/

class RetransModule
{
public:
	RetransModule();
	~RetransModule();

public:
	/** 打开外部通信模块*/
	bool InitRTM();

	/** 关闭外部通信模块*/
	bool EndRTM();

public:
	/**错误码*/
	ErrorTable ErrCode;
};

#endif //S_RETRANS_H_ 
