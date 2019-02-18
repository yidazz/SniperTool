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

	/** ��ʱ����,���ƶ�����ת��Ϊ�ַ�����ʽ,�Թ���DCB�ṹ */
	char szDCBparam[50];
	sprintf_s(szDCBparam, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopsbits);

	/** �����ٽ�� */
	EnterCriticalSection(&S_csSerialPort);

	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	/** ��ָ������,�ú����ڲ��Ѿ����ٽ�������,�����벻Ҫ�ӱ��� */
	if (bIsSuccess)
	{
		bIsSuccess = openPort(portNo);
	}

	/** �ڴ˿���������������Ļ�������С,���������,��ϵͳ������Ĭ��ֵ.
	*  �Լ����û�������Сʱ,Ҫע�������Դ�һЩ,���⻺�������
	*/
	if (bIsSuccess )
	{
		bIsSuccess = SetupComm(S_hComm, SerialPortInQueue, SerialPortOutQueue);
	}

	/** ���ô��ڵĳ�ʱʱ��,����Ϊ0,��ʾ��ʹ�ó�ʱ���� */
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
		// ��ANSI�ַ���ת��ΪUNICODE�ַ���  
		DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, NULL, 0);
		wchar_t *pwText = new wchar_t[dwNum];
		if (!MultiByteToWideChar(CP_ACP, 0, szDCBparam, -1, pwText, dwNum))
		{
			bIsSuccess = TRUE;
		}

		/** ��ȡ��ǰ�������ò���,���ҹ��촮��DCB���� */
		bIsSuccess = GetCommState(S_hComm, &dcb) && BuildCommDCB(pwText, &dcb);
		/** ����RTS flow���� */
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		/** �ͷ��ڴ�ռ� */
		delete[] pwText;
	}

	if (bIsSuccess)
	{
		/** ʹ��DCB�������ô���״̬ */
		bIsSuccess = SetCommState(S_hComm, &dcb);
	}

	/**  ��մ��ڻ����� */
	PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&S_csSerialPort);

	return (TRUE == bIsSuccess);
}

bool SSerialPort::InitPort(UINT portNo, const LPDCB& plDCB)
{
	/** �����ٽ�� */
	EnterCriticalSection(&S_csSerialPort);


	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	/** ��ָ������,�ú����ڲ��Ѿ����ٽ�������,�����벻Ҫ�ӱ��� */
	if (bIsSuccess)
	{
		bIsSuccess = openPort(portNo);
	}
	/** ���ô��ڲ��� */
	if (bIsSuccess)
	{
		bIsSuccess = SetCommState(S_hComm, plDCB);
	}

	/**  ��մ��ڻ����� */
	PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	/** �뿪�ٽ�� */
	LeaveCriticalSection(&S_csSerialPort);

	return (TRUE == bIsSuccess);
}


bool SSerialPort::openPort(UINT portNo)
{
	if (INVALID_HANDLE_VALUE != S_hComm)
	{
		return FALSE;
	}
	/** �����ٽ�� */
	EnterCriticalSection(&S_csSerialPort);

	/** �Ѵ��ڵı��ת��Ϊ�豸�� */
	char szPort[50];
	sprintf_s(szPort, "COM%d", portNo);

	/** ��ָ���Ĵ��� */
	S_hComm = CreateFileA(szPort,  /** �豸��,COM1,COM2�� */
		GENERIC_READ | GENERIC_WRITE, /** ����ģʽ,��ͬʱ��д */
		0,                            /** ����ģʽ,0��ʾ������ */
		NULL,                         /** ��ȫ������,һ��ʹ��NULL */
		OPEN_EXISTING,                /** �ò�����ʾ�豸�������,���򴴽�ʧ�� */
		0,
		0);

	/** �����ʧ�ܣ��ͷ���Դ������ */
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		LeaveCriticalSection(&S_csSerialPort);
		return FALSE;
	}

	/** �˳��ٽ��� */
	LeaveCriticalSection(&S_csSerialPort);

	return TRUE;
}

bool SSerialPort::ClosePort()
{
	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;
	/** �������û���� */
	if (INVALID_HANDLE_VALUE == S_hComm)
	{
		bIsSuccess = FALSE;
	}
	/** ��ָ������,�ú����ڲ��Ѿ����ٽ�������,�����벻Ҫ�ӱ��� */
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
	DWORD dwError = 0;  /** ������ */
	COMSTAT  comstat;   /** COMSTAT�ṹ��,��¼ͨ���豸��״̬��Ϣ */
	memset(&comstat, 0, sizeof(COMSTAT));

	UINT BytesInQue = 0;
	/** �ڵ���ReadFile��WriteFile֮ǰ,ͨ�������������ǰ�����Ĵ����־ */
	if (ClearCommError(S_hComm, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** ��ȡ�����뻺�����е��ֽ��� */
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
	 �鿴�������Ƿ�������
	*****************/

	DWORD dwError = 0;  /** ������ */
	COMSTAT  comstat;   /** COMSTAT�ṹ��,��¼ͨ���豸��״̬��Ϣ */
	memset(&comstat, 0, sizeof(COMSTAT));
	UINT BytesInQue = 0;
	/** �ڵ���ReadFile��WriteFile֮ǰ,ͨ�������������ǰ�����Ĵ����־ */
	if (ClearCommError(S_hComm, &dwError, &comstat))
	{
		BytesInQue = comstat.cbInQue; /** ��ȡ�����뻺�����е��ֽ��� */
	}
	if (0 == BytesInQue)
	{
		return FALSE;
	}

	/****************
	�������������� 
	*****************/
	BOOL  bResult = TRUE;
	DWORD BytesRead = 0;

	/** �ٽ������� */
	EnterCriticalSection(&S_csSerialPort);

	/** �ӻ�������ȡһ���ֽڵ����� */
	bResult = ReadFile(S_hComm, &cRecved, 1, &BytesRead, NULL);
	if ((!bResult))
	{
		/** ��ȡ������,���Ը��ݸô�����������ԭ�� */
		DWORD dwError = GetLastError();

		/** ��մ��ڻ����� */
		PurgeComm(S_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&S_csSerialPort);

		return FALSE;
	}

	/** �뿪�ٽ��� */
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

	/** �ٽ������� */
	EnterCriticalSection(&S_csSerialPort);

	/** �򻺳���д��ָ���������� */
	bResult = WriteFile(S_hComm, pData, length, &BytesToSend, NULL);
	if (!bResult)
	{
		DWORD dwError = GetLastError();
		/** ��մ��ڻ����� */
		PurgeComm(S_hComm, PURGE_TXCLEAR | PURGE_TXABORT);
		LeaveCriticalSection(&S_csSerialPort);

		return FALSE;
	}

	/** �뿪�ٽ��� */
	LeaveCriticalSection(&S_csSerialPort);

	return TRUE;
}

