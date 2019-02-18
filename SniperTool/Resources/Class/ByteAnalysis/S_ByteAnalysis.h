#pragma once
#ifndef S_BYTEANALYSIS_H_  
#define S_BYTEANALYSIS_H_  

#include <Windows.h>  
#include <qDebug.h>  
#include "QueueConfig.h"
#include "S_Vector.h"
#include "S_ByteAnalySelect.h"



class SFirAnalysis
{
public:
	SFirAnalysis();
	~SFirAnalysis();

public:
	/** FLP Ö¡·ÖÎöÆ÷ */
	bool FirAnalysis(char &rRecByte);

private:
	bool FirConfirm(void);

};


//class SSecAnalysis
//{
//public:
//	SSecAnalysis();
//	~SSecAnalysis();
//
//public:
//	/** Ö¡·ÖÎöÆ÷ */
//	bool SecAnalysis(char &rRecByte);
//
//private:
//	SVector *RecByteQueue;
//
//};



#endif //S_BYTEANALYSIS_H_ 
