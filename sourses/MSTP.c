#include "MSTP.h"
#include "Uart.h"



char CheckPack(unsigned char* pData)
{
    unsigned char i;
    unsigned char checkCode=0;
    for(i=0;i<pData[9];i++)
    {
        checkCode ^= pData[3+i];
    }
    if(checkCode!=pData[1])
    {
        for(i=0;i<10;i++)
        {
            pData[i]=0;
        }
        return 0;
    } else{

        return 1;
    }

}

void doPack(pack pData,unsigned char* pack )
{
    unsigned char checkCode=0;
    unsigned char i;
    pack[0] = pData.type;
    pack[2] = pData.cmd;
    pack[9] = pData.length;

    for (i=0;i<pData.length;i++)
    {
        pack[3+i]=pData.cnt[i];
    }
    
    for(i=0;i<pack[9];i++)
    {
        checkCode ^= pack[3+i];
    }

    pack[1]=checkCode;

}

void sendPack(unsigned char* pack )
{
    unsigned char i=10;
    while(i--)
    {
        Uart2SendChar(*pack++);
    }
}

void clearBuffer(unsigned char* pData)
{
    unsigned char i;
    for(i=0;i<10;i++)
    {
        pData[i]=0;
    }
}
