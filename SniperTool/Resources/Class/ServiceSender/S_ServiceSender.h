#pragma once
#ifndef S_SERVICESENDER_H
#define S_SERVICESENDER_H  

#include <Windows.h>  
#include <vector>
#include <qDebug.h>  
#include "S_Vector.h"
#include <iostream>  

using namespace std;


/** ҵ�������� */

class SServiceSender
{
public:
	SServiceSender();
	~SServiceSender();

public:
	bool ServiceSender();

};

#endif //S_SERVICESENDER_H 
