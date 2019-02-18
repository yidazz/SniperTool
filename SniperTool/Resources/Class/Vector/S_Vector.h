#pragma once
#ifndef S_VECTOR_H
#define S_VECTOR_H  

#include <Windows.h>  
#include <vector>
using namespace std;


/** 队列类 */

class SVector
{
public:
	SVector();
	~SVector();

public:
	vector <char> Queue1;
	vector <vector<char>> Queue2;

	/** 同步互斥,临界区保护 */
	CRITICAL_SECTION   S_csVector1;   //互斥操作一维队列
	CRITICAL_SECTION   S_csVector2;   //互斥操作二维队列
};

#endif //S_VECTOR_H 
