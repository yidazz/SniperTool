#pragma once
#ifndef S_OUTSIDECOMMSELECT_H_  
#define S_OUTSIDECOMMSELECT_H_  

#include "S_SerialPort.h"


enum OutSideCommTable {
	NoOutSideCommSet = 0x00,
	/* 串口方式 */
	uSerialPort,

	/* TCP方式 */
	uTCP,

};

class SOutSideCommSelect
{
public:
	/**  外部选择 */
	bool OutSideCommRecSelect(char &rRecByte);

public:
	/**  外部选择 */
	//bool OutSideCommSendSelect(char rRecByte);

};

#endif //S_OUTSIDECOMMSELECT_H_ 
