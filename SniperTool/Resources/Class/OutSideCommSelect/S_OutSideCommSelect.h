#pragma once
#ifndef S_OUTSIDECOMMSELECT_H_  
#define S_OUTSIDECOMMSELECT_H_  

#include "S_SerialPort.h"


enum OutSideCommTable {
	NoOutSideCommSet = 0x00,
	/* ���ڷ�ʽ */
	uSerialPort,

	/* TCP��ʽ */
	uTCP,

};

class SOutSideCommSelect
{
public:
	/**  �ⲿѡ�� */
	bool OutSideCommRecSelect(char &rRecByte);

public:
	/**  �ⲿѡ�� */
	//bool OutSideCommSendSelect(char rRecByte);

};

#endif //S_OUTSIDECOMMSELECT_H_ 
