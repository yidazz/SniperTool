#pragma once
#ifndef S_SERIALPORT_H_  
#define S_SERIALPORT_H_  

#include <Windows.h>  
#include <process.h>  
#include <stdio.h>   
#include "QueueConfig.h"


/** ����ͨ����
*
*  ����ʵ���˶Դ��ڵĻ�������
*
*/
class SSerialPort
{
public:
	SSerialPort(void);
	~SSerialPort(void);

public:
	/** ��ʼ�����ں���
	*
	*  @param:  UINT portNo ���ڱ��,Ĭ��ֵΪ1,��COM1,ע��,������Ҫ����9
	*  @param:  UINT baud   ������,Ĭ��Ϊ115200
	*  @param:  char parity �Ƿ������żУ��,'Y'��ʾ��Ҫ��żУ��,'N'��ʾ����Ҫ��żУ��
	*  @param:  UINT databits ����λ�ĸ���,Ĭ��ֵΪ8������λ
	*  @param:  UINT stopsbits ֹͣλʹ�ø�ʽ,Ĭ��ֵΪ1
	*  @param:  DWORD dwCommEvents Ĭ��ΪEV_RXCHAR,��ֻҪ�շ�����һ���ַ�,�����һ���¼�
	*/
	bool InitPort(UINT  portNo = 1, UINT  baud = CBR_115200, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);

	/** ���ڳ�ʼ������
	*
	*  �������ṩֱ�Ӹ���DCB�������ô��ڲ���
	*/
	bool InitPort(UINT  portNo, const LPDCB& plDCB);

	/** �򿪴���
	*/
	bool openPort(UINT  portNo);

	/** �رմ���
	*/
	bool ClosePort();

	/** �򴮿�д����
	*
	*  ���������е�����д�뵽����
	*/
	bool WriteData(unsigned char* pData, unsigned int length);

	/** ��ȡ���ڻ������е��ֽ���
	*/
	UINT GetBytesInCOM();

	/** ��ȡ���ڽ��ջ�������һ���ֽڵ�����
	*/
	bool ReadChar(char &cRecved);

private:
	/** ���ھ�� */
	HANDLE  S_hComm;

	/** ͬ������,�ٽ������� */
	CRITICAL_SECTION   S_csSerialPort;       //!< �����������  
};

#endif //S_SERIALPORT_H_ 
