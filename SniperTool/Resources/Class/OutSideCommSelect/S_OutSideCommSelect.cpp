#include "S_OutSideCommSelect.h"



bool SOutSideCommSelect::OutSideCommRecSelect(char &rRecByte)
{
	extern OutSideCommTable OutSideCommSet;
	extern SSerialPort *OSCSerialPort;

	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;
	switch (OutSideCommSet)
	{
		/* SerialPort方式 */
		case uSerialPort: bIsSuccess = OSCSerialPort->ReadChar(rRecByte); break;
		/* TCP方式 */
		case uTCP: break;

		default: break;
	}
	return (TRUE == bIsSuccess);
}
