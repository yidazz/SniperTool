#pragma once
#ifndef ERRORTABLE_H_  
#define ERRORTABLE_H_  

enum ErrorTable { 
	NoError = 0x0000,
	SerialPort_InitPort,
	OSCM_CreateSendThread,
	OSCM_CreateRecThread,
	TWDM_CreateThread,
	RTM_CreateThread,
};


#endif //ERRORTABLE_H_ 