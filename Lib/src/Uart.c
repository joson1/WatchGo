#include "Uart.h"


 bit busy=0;
 xdata char buffer[16] = 0;
 xdata char Wptr=0;
 xdata char Rptr=0;


void Uart2Isr() interrupt 8
{
    if(S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy=0;
    }
    if(S2CON & 0x01)
    {
        S2CON &= 0xfe;
        buffer[Wptr++]=S2BUF;
        Wptr &= 0x0f;
        
        
        ////´®¿ÚÃüÁî

        // if (Rptr != Wptr)
        // {

        //     ID=MAX30100_getPartID();
        //     Uart2SendChar(buffer[Rptr++]);
        //     Uart2SendChar(ID);
            
        //     Rptr &= 0x0f;
        // }
        ///////
	
    }
}

void Uart2Init()
{
    S2CON=0x50;
    T2L=BRT;
    T2H=BRT>>8;
    AUXR |= 0x14;
    Wptr=0x00;
    Rptr=0x00;
    busy=0;
    IE2=0x01;
    // EA=1;
}

void Uart2SendChar(char Sdata)
{
    while(busy);
    busy=1;
    S2BUF=Sdata;
}

void Uart2SendStr(char* p)
{
    while(*p)
    {
        Uart2SendChar(*p++);
    }
}
