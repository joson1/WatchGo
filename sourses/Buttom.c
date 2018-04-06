#include "Buttom.h"

#define ptDelay 25 //25*20 500ms

unsigned char timer1Count=0;
unsigned char bButtomPtd=0;

void buttomPtdown_Double()
{

}

void buttomClick()
{


}

void buttomInit()
{
    INTCLKO=EX3;


}

void onButtomPtdown_Isr interrupt 11
{
    timer1Count=0;
    TL1 = 0xC0;		//设置定时初值
	TH1 = 0x63;		//设置定时初值       
    TR1=1;  //定时器1开始计时

    bButtomPtd++;
    if(bButtomPtd>=1)
    {
       buttomPtdown_Double();
        //关闭定时器1
        TR1=0;
    }
    
}

void TM1_Isr() interrupt 3 
{
    timer1Cuont++;
    
    if(timer1Cuont==ptDelay) //500ms超时，按键标志清除
    {
        if(bButtomPtd=1)
        {
            buttomClick();
        }
        bButtomPtd=0;
        timer1Count=0;
    }

   	TL1 = 0xC0;		//设置定时初值
	TH1 = 0x63;		//设置定时初值                               //测试端口
}
