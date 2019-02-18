#pragma once
#ifndef S_BYTEANALYSELECT_H_  
#define S_BYTEANALYSELECT_H_  

#include "S_ByteAnalysis.h"

/** 一代协议宏定义 */

/** 帧头 */
const char ProFir_Header = 0xA5;
/** 帧尾 */
const char ProFir_End = 0xAF;
/** 最小帧长 */
const UINT ProFir_MinLen = 4;

/** 二代协议宏定义 */



enum ProtocolTable {
	NoProtocolSet = 0x00,
	/** FOX Raptor项目使用的协议  ，一代协议
	判定条件
	1、具有 0xA5 的帧头
	2、具有 0xAF 的帧尾
	3、具有 除去校验位本身与帧尾 校验和 正确
	4、帧长大于等于4个字节  (即至少有一个数据)**/

	ProtocolFir,

	/** 独立八通道项目使用的协议   ，二代协议
	判定条件
	**/

	ProtocolSec,

};

class SByteAnalySelect
{
public:
	/** 帧分析器选择 */
	bool AnalysisSelect(char &rRecByte);

};


#endif //S_BYTEANALYSELECT_H_ 
