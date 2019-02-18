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

/** �ⲿͨ��ģ����
*
*  ����ʵ�����ⲿͨ��ģ��Ļ�������
*
*/

class OutSideCommModule
{
public:
	OutSideCommModule();
	~OutSideCommModule();

public:
	/** ���ⲿͨ��ģ��*/
	bool InitOSCM();

	/** �ر��ⲿͨ��ģ��*/
	bool EndOSCM();

	/** �򿪴���ģ��*/
	bool OpenSerialPort();

	/** �رմ���ģ��*/
	bool CloseSerialPort();

public:
	/**������*/
	ErrorTable ErrCode;

};

#endif //S_OUTSIDECOMM_H_ 
