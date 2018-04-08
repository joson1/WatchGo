#include "MAX30100.h"

void MAX30100_writeRegister(unsigned char RAdd,unsigned char Data)
{

    OBIIC_Start();
    OBIIC_SendData(ADDRESS_MAX30100);
    OBIIC_SendACK();
    OBIIC_SendData(RAdd);
    OBIIC_SendACK();
    OBIIC_SendData(Data);
    OBIIC_SendACK();
    OBIIC_Stop();
	

}
char MAX30100_readRegister(unsigned char RAdd)
{
    char Data;
    OBIIC_Start();
    OBIIC_SendData(ADDRESS_MAX30100);
    OBIIC_SendACK();
    OBIIC_SendData(RAdd);
    OBIIC_SendACK();
    OBIIC_Start();
    OBIIC_SendData(ADDRESS_MAX30100+1);
    OBIIC_SendACK();
    Data=OBIIC_RecvData();
    OBIIC_SendNAK();
    OBIIC_Stop();
    return Data;

}

bit MAX30100_Init()
{
    if(MAX30100_getPartID()!=0x11)
    {
        return 0;
    }
		return 1;
}


void MAX30100_restFifo()
{
    MAX30100_writeRegister(ADDRESS_MAX30100_FIFIOEDPtr,0x00);
    MAX30100_writeRegister( ADDRESS_MAX30100_FIFOWRPtr,0);
    MAX30100_writeRegister(ADDRESS_MAX30100_FIFOData,0);
}

unsigned char MAX30100_getPartID()
{
    return MAX30100_readRegister(0xff);
}


void MAX30100_startTemperatureSampling()
{
    MAX30100_writeRegister(ADDRESS_MAX30100_MODECFG,0x08);
}

float MAX30100_getTemperature()
{
    unsigned char integer=MAX30100_readRegister(ADDRESS_MAX30100_TEMP);
    float frac=MAX30100_readRegister(ADDRESS_MAX30100_TEMP+1);
    return frac*0.0625+integer;
}


void MAX30100_readMultiByte(unsigned char address,unsigned char* buffer,unsigned char length)
{
    unsigned char* p=buffer;
    OBIIC_Start();
    OBIIC_SendData(ADDRESS_MAX30100);
    OBIIC_SendACK();
    OBIIC_SendData(address);
    OBIIC_SendACK();
    OBIIC_Start();
    OBIIC_SendData(ADDRESS_MAX30100+1);
    OBIIC_SendACK();
    length--;
    *p=OBIIC_RecvData();
    p++;
    while(length--)
    {
        OBIIC_SendACK();
        *p=OBIIC_RecvData();
        p++;
    }
    OBIIC_SendNAK();
    OBIIC_Stop();


}

void MAX30100_enSPO2()
{
    MAX30100_writeRegister(ADDRESS_MAX30100_SPO2CFG,0x5f);
}
