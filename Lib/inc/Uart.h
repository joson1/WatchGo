#ifndef __UART_H__
#define __UART_H__


#include "STC8.h"


#define FOSC 24000000UL
#define BRT (65536-FOSC/115200/4)
//115200 RxD P10 TxD11  460800


extern bit busy;
extern xdata char buffer[16];
extern xdata char Wptr;
extern xdata char Rptr;


void Uart2SendStr(char* p);
void Uart2SendChar(char Sdata);
void Uart2Init();


#endif
