#include "common.h"
#include "oled.h"

#include "Display.h"
#include "Timer.h"
#include "Uart.h"
#include "MAX30100.h"
#include "MSTP.h"

#define refreashDisplay()  preHourH=Hour/10;preMinuteH=Minute/10; displayHoursH(preHourH);displayHoursL(Hour%10);displayMinuteH(preMinuteH);displayMinuteL(Minute%10);\
							displayIcon_Battery(2,0xff);displayIcon_Bluetooth(0x00)


#define DEBUG
//#include "Power.h"

unsigned char xdata SMode=0;

enum FucState
{
	TimeMode=1,
	HeartRateMode,
	StepMode
};

void main()
{
	pack tmpPack;
	unsigned char tmpCnt[6]=0;
	unsigned char ID=0 ;

	P_SW2=0xb0;
	I2CCFG=0xe0;
	I2CMSST=0x00;

	// MAX30100_startTemperatureSampling();
	
	//	powerInit();

	//Timer0Init();
	SMode=TimeMode;

	// MAX30100_writeRegister(0x06,0x0b);
	// MAX30100_writeRegister(0x01,0xf0);
	// MAX30100_writeRegister(0x09,0x33);

	
	Uart2Init();
	Timer0Init();

	MAX30100_Init();
	shutdown();
	OLED_Init();

	displayHoursH(0);
	displayColon(0xff);
	displayMinuteH(0);
	displayIcon_Battery(2,0xff);
	displayIcon_Bluetooth(0x00);

	Uart2_SendStr("Started!\n");
	



	while(1)
	{


		while(SMode==TimeMode)
		{
			// if(Rptr!=Wptr)
			// {
			// 	Uart2SendChar(buffer[Rptr++]);
			// 	Rptr&=0x09;
			// }
			

			if(bDataComplete)
			{
				bDataComplete=0;

				if(CheckPack(buffer))   //CheckPack(buffer)
				{
					#ifdef DEBUG
					sendPack(&buffer[0]);
					#endif
					switch(buffer[0])
					{
						case 0x00 : switch(buffer[2])
										{
											case 0x02:  resume(); SMode=HeartRateMode;displayHRmodeIcon();
														MAX30100_writeRegister(0x06,0x0b);
														MAX30100_writeRegister(0x01,0xf0);
														MAX30100_writeRegister(0x09,0x33);
														 break;
											case 0x03:  Hour=buffer[3]; Minute=buffer[4];Second=buffer[5];
														refreashDisplay();
														break;
											
											default : break;
										} break;
						case 0x01 : switch(buffer[2])
									{
										case 0x02 : break;
										default : break;
									}break;
						default : break;
					}
					clearBuffer(&buffer[0]);

				}


			}
				
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

		while(SMode==HeartRateMode)
		{
			
			if(bDataComplete)
			{
				bDataComplete=0;
				if(CheckPack(buffer))
				{
					switch(buffer[0])
					{
						case 0x00 : switch(buffer[2])
										{
											case 0x02:  shutdown(); SMode=TimeMode;OLED_Clear(); 
														refreashDisplay();
											
														break;
											case 0x03:  
														tmpCnt[0]=MAX30100_getPartID();
														tmpPack.type=0x01;tmpPack.cmd=0x03;tmpPack.cnt=tmpCnt;tmpPack.length=1;
														doPack(tmpPack,buffer);
														sendPack(buffer);
														break;
											
											default : break;
										} break;
						case 0x01 : switch(buffer[2])
									{
										case 0x02 : break;
										default : break;
									}break;
						default : break;
					}
					clearBuffer(&buffer[0]);

				}


			}
		

			
		}
		while(SMode==StepMode)
		{


		}


	}


}
