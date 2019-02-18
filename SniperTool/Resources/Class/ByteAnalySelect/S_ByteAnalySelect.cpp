#include "S_ByteAnalySelect.h"


bool SByteAnalySelect::AnalysisSelect(char &rRecByte)
{
	extern ProtocolTable ProtocolSet;
	extern SFirAnalysis *OSCFirAnalysis;

	/** 是否有错误发生 */
	BOOL bIsSuccess = TRUE;

	switch (ProtocolSet)
	{
		/* FOX 和 Raptor 协议 */
		case ProtocolFir: bIsSuccess = OSCFirAnalysis->FirAnalysis(rRecByte); break;
		/* 独立八通道项目 协议 */
		//case ProtocolSec: bIsSuccess = OSCByteAnalysis->SecAnalysis(rRecByte); break;

		default: break;
	}
	return (TRUE == bIsSuccess);
}
