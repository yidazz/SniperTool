#include "S_SerialPort.h"  

SSerialPort::SSerialPort(void)
{
	S_hComm = INVALID_HANDLE_VALUE;
	InitializeCriticalSection(&S_csSerialPort);
}

SSerialPort::~SSerialPort(void)
{
	ClosePort();
	DeleteCriticalSection(&S_csSerialPort);
}

bool SSerialPort::InitPort(UINT portNo /*= 1*/, UINT baud /*= CBR_115200*/, char parity /*= 'N'*/,
	UINT databits /*= 8*/, UINT stopsbits /*= 1*/, DWORD dwCommEvents /*= EV_RXCHAR*/)
{

	/** 临时变量,将制定参数转化为字符串形式,以构造DCB结构 */
	char szDCBparam[50];
	sprintf_s(szDCBparam, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopsbits);

	/** 进入临界段 */
	EnterCriticalSection(&S_csSerialPort);

	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	/** 打开指定串口,该函数内部已经有临界区保护,上面请不要加保护 */
	if (bIsSuccess)
	{
		bIsSuccess = openPort(portNo);
	}

	/** 在此可以设置输入输出的缓冲区大小,如果不设置,则系统会设置默认值.
	*  自己设置缓冲区大小时,要注意设置稍大一些,避免缓冲区溢出
	*/
	if (bIsSuccess )
	{
		bIsSuccess = SetupComm(S_hComm, SerialPortInQueue, SerialPortOutQueue);
	}

	/** 设置串口的超时时间,均设为0,表示不使用超时限制 */
	if (bIsSuccess)
	{
		COMMTIMEOUTS  CommTimeouts;
		CommTimeouts.ReadIntervalTimeout = 0;
		CommTimeouts.ReadTotalTimeoutMultiplier = 0;
		CommTimeouts.ReadTotalTimeoutConstant = 0;
		CommTimeouts.WriteTotalTimeoutMultiplier = 0;
		CommTimeouts.WriteTotalTimeoutConstant = 0;
		bIsSuccess = SetCommTimeouts(S_hComm, &CommTimeouts);
	}

	DCB  dcb;
	if (bIsSuccess)
	{
		// 将ANSI字符串转换为UNICODE字符串  
		DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, NULL, 0);
		wchar_t *pwText = new wchar_t[dwNum];
		if (!MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, pwText, dwNum))
		{
			bIsSuccess = TRUE;
		}

		/** 获取当前串口配置参数,并且构造串口DCB参数 */
		bIsSuccess = GetCommState(S_hComm, &dcb) && BuildCommDCB(pwText, &dcb);
		/** 开启RTS flow控制 */
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		/** 释放内存空间 */
		delete[] pwText;
	}

	if (bIsSuccess)
	{
		/** 使用DCB参数配置串口状态 */
		bIsSuccess = SetCommState(S_hComm, &dcb);
	}

	/**  清空串口缓冲区 */
	PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** 离开临界段 */
	LeaveCriticalSection(&S_csSerialPort);

	return (TRUE == bIsSuccess);
}

bool SSerialPort::InitPort(UINT portNo, const LPDCB& plDCB)
{
	/** 进入临界段 */
	EnterCriticalSection(&S_csSerialPort);


	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	/** 打开指定串口,该函数内部已经有临界区保护,上面请不要加保护 */
	if (bIsSuccess)
	{
		bIsSuccess = openPort(portNo);
	}
	/** 配置串口参数 */
	if (bIsSuccess)
	{
		bIsSuccess = SetCommState(S_hComm, plDCB);
	}

	/**  清空串口缓冲区 */
	PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** 离开临界段 */
	LeaveCriticalSection(&S_csSerialPort);

	return (TRUE == bIsSuccess);
}


bool SSerialPort::openPort(UINT portNo)
{
	if (INVALID_HANDLE_VALUE != S_hComm)
	{
		return FALSE;
	}
	/** 进入临界段 */
	EnterCriticalSection(&S_csSerialPort);

	/** 把串口的编号转换为设备名 */
	char szPort[50];
	sprintf_s(szPort, "COM%d", portNo);

	/** 打开指定的串口 */
	S_hComm = CreateFileA(szPort,  /** 设备名,COM1,COM2等 */
		GENERIC_READ | GENERIC_WRITE, /** 访问模式,可同时读写 */
		0,                            /** 共享模式,0表示不共享 */
		NULL,                         /** 安全性设置,一般使用NULL */
		OPEN_EXISTING,                /** 该参数表示设备必须存在,否则创建失败 */
		0,
		0);

	/** 如果打开失败，释放资源并返回 */
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		LeaveCriticalSection(&S_csSerialPort);
		return FALSE;
	}

	/** 退出临界区 */
	LeaveCriticalSection(&S_csSerialPort);

	return TRUE;
}

bool SSerialPort::ClosePort()
{
	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;
	/** 如果串口没被打开 */
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		bIsSuccess = FALSE;
	}
	/** 打开指定串口,该函数内部已经有临界区保护,上面请不要加保护 */
	if (bIsSuccess)
	{
		bIsSuccess = CloseHandle(S_hComm);
	}
	if (bIsSuccess)
	{
		S_hComm = INVALID_HANDLE_VALUE;
	}
	return (TRUE == bIsSuccess);
}

UINT SSerialPort::GetBytesInCOM()
{
	DWORD dwError = 0;  /** 错误码 */
	COMSTAT  comstat;   /** COMSTAT结构体,记录通信设备的状态信息 */
	memset(&comstat, 0, sizeof(COMSTAT));

	UINT BytesInQue = 0;
	/** 在调用ReadFile和WriteFile之前,通过本函数清除以前遗留的错误标志 */
	if (ClearCommError(S_hComm, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** 获取在输入缓冲区中的字节数 */
	}

	return BytesInQue;
}

bool SSerialPort::ReadChar(char &cRecved)
{
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		return FALSE;
	}
	/****************
	 查看缓存区是否有数据
	*****************/

	DWORD dwError = 0;  /** 错误码 */
	COMSTAT  comstat;   /** COMSTAT结构体,记录通信设备的状态信息 */
	memset(&comstat, 0, sizeof(COMSTAT));
	UINT BytesInQue = 0;
	/** 在调用ReadFile和WriteFile之前,通过本函数清除以前遗留的错误标志 */
	if (ClearCommError(S_hComm, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** 获取在输入缓冲区中的字节数 */
	}
	if (0 == BytesInQue)
	{
		return FALSE;
	}

	/****************
	缓存区中有数据 
	*****************/
	BOOL  bResult = TRUE;
	DWORD BytesRead = 0;

	/** 临界区保护 */
	EnterCriticalSection(&S_csSerialPort);

	/** 从缓冲区读取一个字节的数据 */
	bResult = ReadFile(S_hComm, &cRecved, 1, &BytesRead, NULL);
	if ((!bResult))
	{
		/** 获取错误码,可以根据该错误码查出错误原因 */
		DWORD dwError = GetLastError();

		/** 清空串口缓冲区 */
		PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&S_csSerialPort);

		return FALSE;
	}

	/** 离开临界区 */
	LeaveCriticalSection(&S_csSerialPort);

	return (1 == BytesRead);
}

bool SSerialPort::WriteData(unsigned char* pData, unsigned int length)
{
	BOOL   bResult = TRUE;
	DWORD  BytesToSend = 0;
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		return FALSE;
	}

	/** 临界区保护 */
	EnterCriticalSection(&S_csSerialPort);

	/** 向缓冲区写入指定量的数据 */
	bResult = WriteFile(S_hComm, pData, length, &BytesToSend, NULL);
	if (!bResult)
	{
		DWORD dwError = GetLastError();
		/** 清空串口缓冲区 */
		PurgeComm(S_hComm, PURGE_TXCLEAR | PURGE_TXABORT);
		LeaveCriticalSection(&S_csSerialPort);

		return FALSE;
	}

	/** 离开临界区 */
	LeaveCriticalSection(&S_csSerialPort);

	return TRUE;
}

