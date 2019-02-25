#pragma once
#ifndef PROTOCOL_H_  
#define PROTOCOL_H_  

#include <Windows.h>  

/* 公共部分 */

#define MsgDataMaxLen 1000   //




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
	NoThreadNum,          //预留
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

enum MsgStateProtocol {
	NoMsgState,                  // 预留
	MsgUnHandle,                 // 未处理
	MsgHandling,                 // 处理中
	MsgHadHandle,                // 已处理
	MsgStateProtocolTotal,      // 总数
};
enum SpaceStateProtocol {
	SpaceFree,                // 空间空闲 
	SpaceUsed,                 // 空间占用
	SpaceStateProtocolTotal,      // 总数
};

/* 消息结构体 */
typedef struct
{
	/* 状态 */
	MsgStateProtocol MsgState = NoMsgState; //消息状态
	unsigned int DataCount = 0;   //数据个数
	/* 数据 */
	unsigned int ServiceNum = 0;  //消息编号
	ThreadNum SourceNum = NoThreadNum;//来源模块
	ThreadNum DestNum = NoThreadNum;//目的模块
	char Data[MsgDataMaxLen] = { 0 }; //数据
}MESSAGE;


#endif