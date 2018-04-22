#include "Uart.h"
#include "common.h"


bit busy=0;
bit bDataComplete=0;
char xdata buffer[10] = 0;
char xdata Wptr=0;
char xdata Rptr=0;


void Uart2Isr() interrupt 8
{
    if(S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy=0;
    }
    if(S2CON & 0x01)    //½ÓÊÕÖÐ¶Ï
    {
        S2CON &= 0xfe;
        buffer[Wptr++]=S2BUF;
        if(Wptr==10)
        {
            bDataComplete=1;
            Wptr =0;
        } 
        

    
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

void Uart2_SendStr(char* p)
{
    while(*p)
    {
        Uart2SendChar(*p++);
    }
}
