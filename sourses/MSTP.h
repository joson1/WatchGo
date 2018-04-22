#ifndef _MSTP_H_
#define _MSTP_H_

#include "Uart.h"



typedef struct 
{
    unsigned char type;
    unsigned char cmd;
    unsigned char* cnt;
    unsigned char length;

} pack;

extern void clearBuffer(unsigned char* pData);
extern void sendPack(unsigned char* pack );
extern char CheckPack(unsigned char* pData);
extern void doPack(pack pData,unsigned char* pack );
#endif
