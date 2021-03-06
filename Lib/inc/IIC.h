#ifndef IIC_H
#define IIC_H


#include "STC8.h"

#define SDA P24
#define SCL P25

extern void IIC_Start();
extern void IIC_Stop();
extern void IIC_WR_Byte(unsigned char IIC_Byte);
extern void IIC_Wait_Ack();
extern unsigned char IIC_rcvbyte_nack();
extern unsigned char IIC_rcvbyte_ack();
extern void IIC_Nack();



#endif
