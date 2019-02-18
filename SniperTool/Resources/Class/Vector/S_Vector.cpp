#include "S_Vector.h"  

SVector::SVector()
{
	InitializeCriticalSection(&S_csVector1);
	InitializeCriticalSection(&S_csVector2);
}

SVector::~SVector()
{
	vector<char>().swap(Queue1);
	vector<vector<char>>().swap(Queue2);
	DeleteCriticalSection(&S_csVector1);
	DeleteCriticalSection(&S_csVector2);
}
