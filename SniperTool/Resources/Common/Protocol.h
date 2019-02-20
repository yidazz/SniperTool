#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

#include <Windows.h>  
#include <vector>
using std::vector;
/* 公共部分 */




enum ServiceMsgProtocol {
	ServiceNum1,              // 业务编号低位
	ServiceNum2,              // 业务编号中低位
	ServiceNum3,              // 业务编号中高位
	ServiceNum4,              // 业务编号高位
	ServiceSourceNum,                  // 来源号
	ServiceDestNum,                    // 目的号
	ServiceMsgProtocolTotal,        // 总数
	/* 剩余字节格式按照各模块业务表要求的格式发送 */
};

enum ThreadNum {
	TWDThreadNum,             //线程看门狗线程
	RTThreadNum,              //转发器线程
	OSCSendThreadNum,         //发送线程
	OSCRecThreadNum,          //接收线程
	ThreadNumTotal,       // 总数
};

enum ModuleNum {
	NoModNum,             // 无模块
	TWDModNum,             // 线程看门狗模块
	RTModNum,             // 转发器模块
	OSCSendModNum,            // 外部交流器模块
	OSCRecModNum,          // 外部交流器模块
	ModuleNumTotal,       // 总数
};

enum InBuffMsgProtocol {
	InSource,                  // 来源号
	InDest,                    // 目的号
	InIndex,                   // 消息索引
	InBuffMsgProtocolTotal,       // 总数
};

class MESSAGE
{
//public:
//	~MESSAGE()
//	{
//		vector<char>().swap(Data);
//	}
public:
	unsigned int ServiceNum;//消息编号
	ThreadNum SourceNum;//来源模块
	ThreadNum DestNum;//目的模块
	char Data[3000];
};


#endif //PROTOCOL_H_ 