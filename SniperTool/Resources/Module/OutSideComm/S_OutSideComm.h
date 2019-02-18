#pragma once
#ifndef S_OUTSIDECOMM_H_  
#define S_OUTSIDECOMM_H_  

#include <Windows.h>  
#include "ErrorTable.h"
#include "S_SerialPort.h"  
#include "S_Thread.h"
#include "S_ByteAnalysis.h"
#include "S_TimerUs.h"  
#include "S_OutSideCommSelect.h"
#include "S_ByteAnalySelect.h"
#include "S_ServiceSender.h"  
#include "S_Vector.h"  

/** 外部通信模块类
*
*  本类实现了外部通信模块的基本功能
*
*/

class OutSideCommModule
{
public:
	OutSideCommModule();
	~OutSideCommModule();

public:
	/** 打开外部通信模块*/
	bool InitOSCM();

	/** 关闭外部通信模块*/
	bool EndOSCM();

	/** 打开串口模块*/
	bool OpenSerialPort();

	/** 关闭串口模块*/
	bool CloseSerialPort();

public:
	/**错误码*/
	ErrorTable ErrCode;

};

#endif //S_OUTSIDECOMM_H_ 
