#pragma once
#ifndef S_SERVICESENDER_H
#define S_SERVICESENDER_H  

#include <Windows.h>  
#include <vector>
#include <qDebug.h>  
#include "S_Vector.h"
#include "Protocol.h"
#include <iostream>  

using namespace std;


/** 业务发送器类 */

class SServiceSender
{
public:
	SServiceSender();
	~SServiceSender();

public:
	bool ServiceSender(MESSAGE* MessageIndex);

};

#endif //S_SERVICESENDER_H 
