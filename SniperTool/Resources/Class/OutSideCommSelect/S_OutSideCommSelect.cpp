#include "S_OutSideCommSelect.h"



bool SOutSideCommSelect::OutSideCommRecSelect(char &rRecByte)
{
	extern OutSideCommTable OutSideCommSet;
	extern SSerialPort *OSCSerialPort;

	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;
	switch (OutSideCommSet)
	{
		/* SerialPort��ʽ */
		case uSerialPort: bIsSuccess = OSCSerialPort->ReadChar(rRecByte); break;
		/* TCP��ʽ */
		case uTCP: break;

		default: break;
	}
	return (TRUE == bIsSuccess);
}
