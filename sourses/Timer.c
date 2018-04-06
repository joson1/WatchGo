#include "Timer.h"
#include "STC8.h"

    unsigned int xdata TickCount=0;
    unsigned int xdata Hour=0;
    unsigned int xdata Minute=0;
    unsigned int xdata Second=0;
    unsigned int xdata preHourH;
    unsigned int xdata preMinuteH;
    bit isHourChange=1;
    bit isMinuteChange=1;
    bit isSecondChange=1;

void Timer0Init(void)		//20毫秒@24.000MHz
{  
    
	EA=1;
    AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xC0;		//设置定时初值
	TH0 = 0x63;		//设置定时初值
	ET0 = 1;                                    //???????
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//20毫秒@24.000MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xC0;		//设置定时初值
	TH1 = 0x63;		//设置定时初值
	TF1 = 0;		//清除TF1标志
    ET1=1;
	TR1 = 0;		//定时器1不计时
}


void Tick_20msIsr() interrupt 1
{
    TickCount++;
    if(TickCount==50)
    {
        Second++;
        isSecondChange=1;
        TickCount=0;
        if(Second==60)
        {
            Minute++;
            isMinuteChange=1;
            Second=0;
            if(Minute==60)
            {
                Hour++;
                isHourChange=1;
                Minute=0;

            }
        }
    }

	TL0 = 0xC0;		//设置定时初值
	TH0 = 0x63;		//设置定时初值


}


