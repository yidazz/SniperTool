#pragma once
#ifndef S_BYTEANALYSELECT_H_  
#define S_BYTEANALYSELECT_H_  

#include "S_ByteAnalysis.h"

/** һ��Э��궨�� */

/** ֡ͷ */
const char ProFir_Header = 0xA5;
/** ֡β */
const char ProFir_End = 0xAF;
/** ��С֡�� */
const UINT ProFir_MinLen = 4;

/** ����Э��궨�� */



enum ProtocolTable {
	NoProtocolSet = 0x00,
	/** FOX Raptor��Ŀʹ�õ�Э��  ��һ��Э��
	�ж�����
	1������ 0xA5 ��֡ͷ
	2������ 0xAF ��֡β
	3������ ��ȥУ��λ������֡β У��� ��ȷ
	4��֡�����ڵ���4���ֽ�  (��������һ������)**/

	ProtocolFir,

	/** ������ͨ����Ŀʹ�õ�Э��   ������Э��
	�ж�����
	**/

	ProtocolSec,

};

class SByteAnalySelect
{
public:
	/** ֡������ѡ�� */
	bool AnalysisSelect(char &rRecByte);

};


#endif //S_BYTEANALYSELECT_H_ 
