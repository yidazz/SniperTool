#pragma once
#ifndef S_SERIALPORT_H_  
#define S_SERIALPORT_H_  

#include <Windows.h>  
#include <process.h>  
#include <stdio.h>   
#include "QueueConfig.h"


/** 串口通信类
*
*  本类实现了对串口的基本操作
*
*/
class SSerialPort
{
public:
	SSerialPort(void);
	~SSerialPort(void);

public:
	/** 初始化串口函数
	*
	*  @param:  UINT portNo 串口编号,默认值为1,即COM1,注意,尽量不要大于9
	*  @param:  UINT baud   波特率,默认为115200
	*  @param:  char parity 是否进行奇偶校验,'Y'表示需要奇偶校验,'N'表示不需要奇偶校验
	*  @param:  UINT databits 数据位的个数,默认值为8个数据位
	*  @param:  UINT stopsbits 停止位使用格式,默认值为1
	*  @param:  DWORD dwCommEvents 默认为EV_RXCHAR,即只要收发任意一个字符,则产生一个事件
	*/
	bool InitPort(UINT  portNo = 1, UINT  baud = CBR_115200, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);

	/** 串口初始化函数
	*
	*  本函数提供直接根据DCB参数设置串口参数
	*/
	bool InitPort(UINT  portNo, const LPDCB& plDCB);

	/** 打开串口
	*/
	bool openPort(UINT  portNo);

	/** 关闭串口
	*/
	bool ClosePort();

	/** 向串口写数据
	*
	*  将缓冲区中的数据写入到串口
	*/
	bool WriteData(unsigned char* pData, unsigned int length);

	/** 获取串口缓冲区中的字节数
	*/
	UINT GetBytesInCOM();

	/** 读取串口接收缓冲区中一个字节的数据
	*/
	bool ReadChar(char &cRecved);

private:
	/** 串口句柄 */
	HANDLE  S_hComm;

	/** 同步互斥,临界区保护 */
	CRITICAL_SECTION   S_csSerialPort;       //!< 互斥操作串口  
};

#endif //S_SERIALPORT_H_ 
