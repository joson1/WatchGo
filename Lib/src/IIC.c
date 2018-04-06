#include "IIC.h"

void IIC_Start()
{
    SCL=1;
    SDA=1;
    SDA=0;
    SCL=0;
}
void IIC_Stop()
{
    SCL=1;
    SDA=0;
    SDA=1;
}

void IIC_WR_Byte(unsigned char IIC_Byte)
{
    unsigned char a=0;
    for(a=0;a<8;a++)
    {
        SDA=IIC_Byte>>7;
        IIC_Byte=IIC_Byte<<1;
        Delay5us();
        SCL=1;
        Delay5us();
        SCL=0;
        Delay5us();
    }
    SDA=1;
    SCL=1;

}
//void IIC_Wait_Ack()
//{
    
//    SCL=1;
//    SCL=0;
//}
void IIC_Wait_Ack()
{
    unsigned char b;
    while(SDA)
    {
        b++;
        if(b>30)
        {
            SCL=0;
        
        }
    }
}
void IIC_Nack()
{
    SCL=0;
    SDA=1;
    SCL=1;
    Delay5us();
    SCL=0;
    Delay5us();
}
unsigned char IIC_rcvbyte_nack()
{
    unsigned char a,dat;
    SDA=1;
    Delay5us(); 
    for(a=0;a<8;a++)
    {
        SCL=1;
        Delay5us();
        dat<<=1;
        dat|=SDA;
        Delay5us();
        SCL=0;
        Delay5us();

    }

    //给出NACK信号
   //IIC_Nack();
 //   _nop_();
 //   _nop_();
  //  SCL=0;
   // _nop_();
 //   _nop_();
  //  SDA=1;
   // _nop_();
    //_nop_();
   // SCL=1;
  //  _nop_();
   // _nop_();
   // SCL=0;
  //  _nop_();
   // _nop_();
    return dat;
}
unsigned char IIC_rcvbyte_ack()
{
    unsigned char retc;
    unsigned char bitcnt;
    retc=0;
    SDA=1;
    for(bitcnt=0;bitcnt<8;bitcnt++)
    {
        _nop_();
        _nop_();
        SCL=0;
        _nop_();
        _nop_();
        SCL=1;
        _nop_();
        _nop_();
        retc=retc<<1;
        if(SDA==1)
        retc=retc+1;
        _nop_();
        _nop_();
    }
    //给出ACK信号
    _nop_();
    _nop_();
    SCL=0;
    _nop_();
    _nop_();
    SDA=0;
    _nop_();
    _nop_();
    SCL=1;
    _nop_();
    _nop_();
    SCL=0;
    _nop_();
    _nop_();
    return(retc);
}
