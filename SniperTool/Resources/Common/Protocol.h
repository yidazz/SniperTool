#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

/* 公共部分 */

enum InsideProtocol {
	InServiceNum1,             // 业务编号低位
	InServiceNum2,             // 业务编号中低位
	InServiceNum3,             // 业务编号中高位
	InServiceNum4,             // 业务编号高位
	InSource,                  // 来源号
	InDest,                    // 目的号
	InsideProtocolTotal,       // 总数
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
#endif //PROTOCOL_H_ 