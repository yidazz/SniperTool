#pragma once
#ifndef S_VECTOR_H
#define S_VECTOR_H  

#include <Windows.h>  
#include <vector>
using namespace std;


/** ������ */

class SVector
{
public:
	SVector();
	~SVector();

public:
	vector <char> Queue1;
	vector <vector<char>> Queue2;

	/** ͬ������,�ٽ������� */
	CRITICAL_SECTION   S_csVector1;   //�������һά����
	CRITICAL_SECTION   S_csVector2;   //���������ά����
};

#endif //S_VECTOR_H 
