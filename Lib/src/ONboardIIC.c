#include "ONboard_IIC.h"


char OBIIC_RecvData()
{
    I2CMSCR = 0x04;                             //∑¢ÀÕRECV√¸¡Ó
    OBIIC_Wait();
    return I2CRXD;
}


void delay()
{
    int i;
    for(i=0;i<3000;i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_(); 
    }

}
