#include "S_ByteAnalySelect.h"


bool SByteAnalySelect::AnalysisSelect(char &rRecByte)
{
	extern ProtocolTable ProtocolSet;
	extern SFirAnalysis *OSCFirAnalysis;

	/** �Ƿ��д����� */
	BOOL bIsSuccess = TRUE;

	switch (ProtocolSet)
	{
		/* FOX �� Raptor Э�� */
		case ProtocolFir: bIsSuccess = OSCFirAnalysis->FirAnalysis(rRecByte); break;
		/* ������ͨ����Ŀ Э�� */
		//case ProtocolSec: bIsSuccess = OSCByteAnalysis->SecAnalysis(rRecByte); break;

		default: break;
	}
	return (TRUE == bIsSuccess);
}
