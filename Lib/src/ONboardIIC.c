#include "ONboard_IIC.h"

char OBIIC_RecvData()
{
    I2CMSCR = 0x04;                             //∑¢ÀÕRECV√¸¡Ó
    OBIIC_Wait();
    return I2CRXD;
}
