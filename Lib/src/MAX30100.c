#include "MAX30100.h"

SensorReadout xdata readoutBuffer[16];
SensorReadout xdata *head;
SensorReadout xdata *tail;
unsigned short MAX30100_count;

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


void MAX30100_restFifo()
{
    MAX30100_writeRegister(ADDRESS_MAX30100_FIFIOEDPtr,0);
    MAX30100_writeRegister(ADDRESS_MAX30100_FIFOWRPtr,0);
    MAX30100_writeRegister(ADDRESS_MAX30100_FIFOData,0);
}

unsigned char MAX30100_getPartID()
{
    return MAX30100_readRegister(0xff);
}


void MAX30100_startTemperatureSampling()
{
    unsigned char modeConfig=MAX30100_readRegister(MAX30100_REG_MODE_CONFIGURATION);
    modeConfig |= MAX30100_MC_TEMP_EN;
    MAX30100_writeRegister(MAX30100_REG_MODE_CONFIGURATION,modeConfig);

}

char MAX30100_isTempertuareReady()
{
    return !(MAX30100_readRegister(MAX30100_REG_MODE_CONFIGURATION)&MAX30100_MC_TEMP_EN);
}

////////////////////////
float MAX30100_retrieveTemperature()
{
    unsigned char integer=MAX30100_readRegister(ADDRESS_MAX30100_TEMP);
    float frac=MAX30100_readRegister(ADDRESS_MAX30100_TEMP+1);
    return frac*0.0625+integer;
}
/////////////////////////

void MAX30100_readMultiByte(unsigned char address,unsigned char* MAX30100_buffer,unsigned char length)
{
    unsigned char* p=MAX30100_buffer;
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


char MAX30100_Init()
{
    if(MAX30100_getPartID != 0x11)
    {return 0;}

    MAX30100_setMode(MAX30100_DEFAULT_MODE);
    MAX30100_setLedsPulseWidth(MAX30100_DEFAULT_PULSE_WIDTH);
    MAX30100_setSamplingRate(MAX30100_DEFAULT_SAMPLING_RATE);
    MAX30100_setLedsCurrent(MAX30100_DEFAULT_IR_LED_CURRENT,MAX30100_DEFAULT_RED_LED_CURRENT);
    MAX30100_setHighresModeEnabled(1);

    return 1;

}


void MAX30100_setMode(Mode mode)
{
    MAX30100_writeRegister(MAX30100_REG_MODE_CONFIGURATION,mode);
}

void MAX30100_setLedsPulseWidth(LEDPulseWidth ledPulseWidth)
{
    unsigned char previous = MAX30100_readRegister(MAX30100_REG_SPO2_CONFIGURATION);
    MAX30100_writeRegister(MAX30100_REG_SPO2_CONFIGURATION, (previous & 0xfc) | ledPulseWidth);
}

void MAX30100_setSamplingRate(SamplingRate samplingRate)
{
    unsigned char previous = MAX30100_readRegister(MAX30100_REG_SPO2_CONFIGURATION);
    MAX30100_writeRegister(MAX30100_REG_SPO2_CONFIGURATION, (previous & 0xe3) | (samplingRate << 2));
}

void MAX30100_setLedsCurrent(LEDCurrent irLedCurrent, LEDCurrent redLedCurrent)
{
    MAX30100_writeRegister(MAX30100_REG_LED_CONFIGURATION, redLedCurrent << 4 | irLedCurrent);
}

void MAX30100_setHighresModeEnabled(char enabled)
{
    unsigned char previous = MAX30100_readRegister(MAX30100_REG_SPO2_CONFIGURATION);
    if (enabled) {
        MAX30100_writeRegister(MAX30100_REG_SPO2_CONFIGURATION, previous | MAX30100_SPC_SPO2_HI_RES_EN);
    } else {
        MAX30100_writeRegister(MAX30100_REG_SPO2_CONFIGURATION, previous & ~MAX30100_SPC_SPO2_HI_RES_EN);
    }


}

void MAX30100_update()
{
    readFifoData();
}

char MAX30100_getRawValues(unsigned short *ir, unsigned short *red)
{
    if(MAX30100_count!=0)
    {
        SensorReadout readout;
        readout=MAX30100_Buffer_pop();

        *ir=readout.ir;
        *red=readout.red;

        return 1;
    } else 
    {
        return 0;
    }
}
///////////////////////
char MAX30100_Buffer_Push(SensorReadout value)
{
    if(++tail == readoutBuffer+16)
    {
        tail=readoutBuffer;
    }
    *tail = value;
    if(MAX30100_count == 16)
    {
        if(++head == readoutBuffer+16){ head=readoutBuffer; }
        return 0;
    } else{
        if(MAX30100_count++==0) head=tail;
        return 1;
    }

}
//////////////////////
SensorReadout MAX30100_Buffer_pop()
{
    //if(MAX30100_count<0)  ;    ////ERROR crash
    SensorReadout result;
    result = *tail--;
    if(tail<readoutBuffer) { tail=readoutBuffer + 15; }
    MAX30100_count--;
    return result;
    
}
///////////////////////

void readFifoData()
{
    unsigned char xdata MAX30100_buffer[MAX30100_FIFO_DEPTH*4]; //MAX30100_FIFO_DEPTH*4
    unsigned char xdata toRead;
    unsigned char i;

    toRead = (MAX30100_readRegister(MAX30100_REG_FIFO_WRITE_POINTER) - MAX30100_readRegister(MAX30100_REG_FIFO_READ_POINTER)) & (MAX30100_FIFO_DEPTH-1);

    if (toRead) {
        MAX30100_readMultiByte(MAX30100_REG_FIFO_DATA, MAX30100_buffer, 4 * toRead);

        for (i=0 ; i < toRead ; ++i) {
            // Warning: the values are always left-aligned
            SensorReadout SRtemp;
            SRtemp.ir=(unsigned short)((MAX30100_buffer[i*4] << 8) | MAX30100_buffer[i*4 + 1]);
            SRtemp.red=(unsigned short)((MAX30100_buffer[i*4 + 2] << 8) | MAX30100_buffer[i*4 + 3]);
            MAX30100_Buffer_Push(SRtemp);
        }
    }
}




void shutdown()
{
    unsigned char modeConfig=MAX30100_readRegister(MAX30100_REG_MODE_CONFIGURATION);
    modeConfig |= MAX30100_MC_SHDN;
    MAX30100_writeRegister(MAX30100_REG_MODE_CONFIGURATION,modeConfig);

}
void resume()
{
    unsigned char modeConfig=MAX30100_readRegister(MAX30100_REG_MODE_CONFIGURATION);
    modeConfig &= ~MAX30100_MC_SHDN;
    MAX30100_writeRegister(MAX30100_REG_MODE_CONFIGURATION,modeConfig);
}
