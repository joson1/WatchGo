#include "Power.h"

unsigned char xdata powerStat=0;

void powerInit()
{

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x31);
    OBIIC_SendData(0xf4);
    OBIIC_Stop();

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x12);
    OBIIC_SendData(0xae);
    OBIIC_Stop();           //power output control

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x27);
    OBIIC_SendData(0xe8);
    OBIIC_Stop();           //LOD4

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x28);
    OBIIC_SendData(0xff);
    OBIIC_Stop();           //LOD2/3

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x82);
    OBIIC_SendData(0x80);
    OBIIC_Stop();           //ADC enable

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x84);
    OBIIC_SendData(0x08);
    OBIIC_Stop();           //ADC set

    //IRQ set
    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x40);
    OBIIC_SendData(0x00);
    OBIIC_Stop();

    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x41);
    OBIIC_SendData(0x0c);
    OBIIC_Stop();           //charging and changing coplete interrupt enable

    INTCLKO=EX4;
}

void getBatteryState()
{
    unsigned char stats=0;
    unsigned int V=0;
    
    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x78);
    OBIIC_Start();
    OBIIC_SendData(0x69);
    stats=OBIIC_RecvData();

    V|=stats;
    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x79);
    OBIIC_Start();
    OBIIC_SendData(0x69);
    stats=OBIIC_RecvData();
    V<<=4;
    V|=stats;
    if(V>3000)
    {
        powerStat=1;
        if(V>3500)
        {
            powerStat=2;
            if(V>3800) powerStat=3;
        }
    }

}

void powerRequest_Isr() interrupt 16
{
    unsigned char stats=0;
    OBIIC_Start();
    OBIIC_SendData(0x68);
    OBIIC_SendData(0x45);
    OBIIC_Start();
    OBIIC_SendData(0x69);
    stats=OBIIC_RecvData();

    if(stats&0x08)  powerStat=4;
    if(stats&0x04)  powerStat=3;

}
