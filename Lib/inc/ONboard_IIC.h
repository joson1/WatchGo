#ifndef ONBOARD_IIC_H
#define ONBOARD_IIC_H

#include "STC8.h"

#define obSDA =P14;
#define obSCL =P15;

#define OBIIC_Wait() while(!(I2CMSST&0x40));\
                    I2CMSST &= ~0x40

#define OBIIC_Start() I2CMSCR = 0x01; OBIIC_Wait()

#define OBIIC_SendData(Data) I2CTXD = Data; I2CMSCR = 0x02; OBIIC_Wait()

#define OBIIC_RecvACK() I2CMSCR = 0x03;OBIIC_Wait()

#define OBIIC_SendACK() I2CMSST = 0x00;I2CMSCR = 0x05;OBIIC_Wait()

#define OBIIC_SendNAK() I2CMSST = 0x01;I2CMSCR = 0x05;OBIIC_Wait()

#define OBIIC_Stop() I2CMSCR = 0x06;OBIIC_Wait()



extern char OBIIC_RecvData();


#endif
