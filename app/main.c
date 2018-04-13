#include "common.h"
#include "oled.h"

#include "Display.h"
#include "Timer.h"
#include "Uart.h"
#include "MAX30100.h"
//#include "Power.h"



enum FucState
{
	TimeMode=1,
	HeartRateMode,
	StepMode
};

void main()
{
	unsigned char xdata Mode;
	unsigned char ID=0 ;
	
	P_SW2=0xb0;
	I2CCFG=0xe0;
	I2CMSST=0x00;

	// MAX30100_startTemperatureSampling();
	
	//	powerInit();

	Timer0Init();
	Mode=TimeMode;

	MAX30100_writeRegister(0x06,0x0b);
	MAX30100_writeRegister(0x01,0xf0);
	MAX30100_writeRegister(0x09,0x33);
	
	Uart2Init();
	Timer0Init();

	OLED_Init();

	displayHoursH(0);
	displayColon(0xff);
	displayMinuteH(0);
	displayIcon_Battery(2,0xff);
	displayIcon_Bluetooth(0x00);

	Uart2SendStr("Started!\n");
	



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
