#include "common.h"
#include "oled.h"
#include "MAX30100.h"
#include "Display.h"
#include "Timer.h"
//#include "Power.h"

unsigned char xdata Mode;

enum FucState
{
	TimeMode=1,
	HeartRateMode,
	StepMode
};

void main()
{


	P_SW2=0xb0;
	I2CCFG=0xe0;
	I2CMSST=0x00;


	//char Temperature=0;
	//char ID;

	//ID=MAX30100_getPartID();
	//MAX30100_startTemperatureSampling();
	OLED_Init();
//	powerInit();
	 displayHoursH(0);
	 displayHoursL(0);
	 displayColon(0xff);
	 displayMinuteH(0);
	 displayMinuteL(0);
	displayIcon_Battery(4,0xff);
	displayIcon_Bluetooth(0xff);
	Timer0Init();
	Mode=TimeMode;
	while(1)
	{
		while(Mode==TimeMode)
		{
				
		if(isSecondChange)
		{
			displayColon(0x00);
		
			isSecondChange=0;
		}

		if(TickCount==25)	displayColon(0xff);

		if(isMinuteChange)
		{
			displayMinuteL(Minute%10);
			if((Minute/10)!=preMinuteH)
			{ 
				preMinuteH=Minute/10;
				displayMinuteH(preMinuteH);
				
			}
			isMinuteChange=0;

		}
		if(isHourChange)
		{
			displayHoursL(Hour%10);
			if((Hour/10)!=preHourH) 
			{
				preHourH=Hour/10;
				displayHoursH(preHourH);
			}
			isHourChange=0;
		}


		
	//  getBatteryState();
	//  displayIcon_Battery(4,0xff);
		
	
		}

		while(Mode==HeartRateMode)
		{

		}
		while(Mode==StepMode)
		{


		}


	}

	
}
