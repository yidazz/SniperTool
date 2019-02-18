#pragma once
#ifndef S_TIMERUS_H
#define S_TIMERUS_H  

#include <Windows.h>
#include <chrono>

/** 高精度定时器类
*
*  本类实现了微秒级定时器
*
*/

class STimerUs
{
public:
	STimerUs();
	~STimerUs();

public:
	void Zero();
	UINT Timer();

private:
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::microseconds res;

private:
	clock::time_point Tim;
};

#endif //S_TIMERUS_H 
