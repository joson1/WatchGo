#ifndef MAX30100_H
#define MAX30100_H

#include "ONboard_IIC.h"
#include "common.h"

#define ADDRESS_MAX30100_INTSTATUS 0x00
#define ADDRESS_MAX30100_INTEN 0x01
#define ADDRESS_MAX30100_FIFOWRPtr 0x02
#define ADDRESS_MAX30100_OFCounter 0x03
#define ADDRESS_MAX30100_FIFIOEDPtr 0x04
#define ADDRESS_MAX30100_FIFOData 0x05
#define ADDRESS_MAX30100_MODECFG 0x06
#define ADDRESS_MAX30100_SPO2CFG 0x07
#define ADDRESS_MAX30100_LEDCFG 0x09

#define ADDRESS_MAX30100 0xAE
#define ADDRESS_MAX30100_TEMP 0x16

#define ADDRESS_MAX30100_RevID 0xFE
#define ADDRESS_MAX30100_PartID 0xFF


extern bit MAX30100_Init();
extern char MAX30100_readRegister(unsigned char RAdd);
extern void MAX30100_writeRegister(unsigned char RAdd,unsigned char Data);
extern float MAX30100_getTemperature();
extern void MAX30100_startTemperatureSampling();
extern unsigned char MAX30100_getPartID();
extern void MAX30100_restFifo();
#endif
