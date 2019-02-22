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

/** ת����ģ����
*
*  ����ʵ����ת����ģ��Ļ�������
*
*/

class RetransModule
{
public:
	RetransModule();
	~RetransModule();

public:
	/** ���ⲿͨ��ģ��*/
	bool InitRTM();

	/** �ر��ⲿͨ��ģ��*/
	bool EndRTM();

public:
	/**������*/
	ErrorTable ErrCode;
};

#endif //S_RETRANS_H_ 
