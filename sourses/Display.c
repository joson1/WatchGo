#include "Display.h"
#include "bmp.h"
#include "Timer.h"

void clearNum(unsigned char x,unsigned char y,unsigned int Length,unsigned int width)
{
	unsigned int i,h;
	for(i=0;i<Length;i++)
	{
		OLED_Set_Pos(x+i,y);
		for(h=0;h<width;h++)
		{
			OLED_WR_Byte(0,OLED_DATA);
		}
		
	}    
}

void displayHoursH(unsigned char NUM)
{
    unsigned char* pNUM=&TimerNUM[NUM][0];
    clearNum(PosHoursH_X,PosHoursH_Y,TimerNUM_Length,TimerNUM_Width);
    OLED_Draw(PosHoursH_X,PosHoursH_Y,TimerNUM_Length,TimerNUM_Width,pNUM);


}
void displayHoursL(unsigned char NUM)
{
    unsigned char* pNUM=&TimerNUM[NUM][0];
    clearNum(PosHoursL_X,PosHoursL_Y,TimerNUM_Length,TimerNUM_Width);
    OLED_Draw(PosHoursL_X,PosHoursL_Y,TimerNUM_Length,TimerNUM_Width,pNUM);


}

void displayMinuteH(unsigned char NUM)
{
    unsigned char* pNUM=&TimerNUM[NUM][0];
    clearNum(PosMinuteH_X,PosMinuteH_Y,TimerNUM_Length,TimerNUM_Width);
    OLED_Draw(PosMinuteH_X,PosMinuteH_Y,TimerNUM_Length,TimerNUM_Width,pNUM);


}

void displayMinuteL(unsigned char NUM)
{
    unsigned char* pNUM=&TimerNUM[NUM][0];
    clearNum(PosMinuteL_X,PosMinuteL_Y,TimerNUM_Length,TimerNUM_Width);
    OLED_Draw(PosMinuteL_X,PosMinuteL_Y,TimerNUM_Length,TimerNUM_Width,pNUM);


}

// void displayColon()
// {
//     OLED_Draw(PosColon_X,PosColon_Y,4,2,Colon);
// }

void displayColon(unsigned char cls)  //0x00清除 00xff显示
{
  	unsigned char i,h;
		unsigned char* p;
		p=Colon;
	//OLED_Set_Pos(x,y);
	for(i=0;i<4;i++)
	{
		OLED_Set_Pos(PosColon_X+i,PosColon_Y);
		for(h=0;h<2;h++)
		{
			OLED_WR_Byte((*p)&cls,OLED_DATA);
			p++;
		}
		
	}
}


void displayIcon_Bluetooth(unsigned char cls)  //0x00清除 00xff显示
{
  	unsigned char i,h;
		unsigned char* p;
		p=iconBluetooth;
	//OLED_Set_Pos(x,y);
	for(i=0;i<17;i++)
	{
		OLED_Set_Pos(PosBluetooht_X+i,PosBluetooht_Y);
		for(h=0;h<2;h++)
		{
			OLED_WR_Byte((*p)&cls,OLED_DATA);
			p++;
		}
		
	}
}

void displayIcon_Battery(unsigned char state,unsigned char cls)  //0x00清除 00xff显示 state 0empty 1 2 3full 4charging
{
  	unsigned char i,h;
		unsigned char* p;
		p=&iconBattery[state][0];
	//OLED_Set_Pos(x,y);
	for(i=0;i<28;i++)
	{
		OLED_Set_Pos(PosBattery_X+i,PosBattery_Y);
		for(h=0;h<2;h++)
		{
			OLED_WR_Byte((*p)&cls,OLED_DATA);
			p++;
		}
		
	}
}

void DisplayOFF()
{
	OLED_WR_Byte(0xae,OLED_CMD);

}

void DisplayON()
{
	OLED_WR_Byte(0xaf,OLED_CMD);
	displayHoursH(Hour/10);
	displayHoursL(Hour%10);
	displayMinuteH(Minute/10);
	displayMinuteH(Minute%10);
	
}
