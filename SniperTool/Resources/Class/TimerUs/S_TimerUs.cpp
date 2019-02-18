#include "S_TimerUs.h"  

STimerUs::STimerUs()
{
	Zero();
}

STimerUs::~STimerUs()
{
}

void STimerUs::Zero()
{
	Tim = clock::now();
}

UINT STimerUs::Timer()
{
	clock::time_point t1 = clock::now();
	UINT LastTimer = std::chrono::duration_cast<res>(t1 - Tim).count();
	return (LastTimer);
}
