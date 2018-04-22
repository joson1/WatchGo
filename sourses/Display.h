#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "oled.h"

#define PosHoursH_X 34
#define PosHoursH_Y 0
#define PosHoursL_X 55
#define PosHoursL_Y 0
#define PosMinuteH_X 85
#define PosMinuteH_Y 0
#define PosMinuteL_X 106
#define PosMinuteL_Y 0
#define PosColon_X 77
#define PosColon_Y 1
#define TimerNUM_Length 20
#define TimerNUM_Width 4
#define PosBluetooht_X 0
#define PosBluetooht_Y 2
#define PosBattery_X 0
#define PosBattery_Y 0



extern void clearNum(unsigned char x,unsigned char y,unsigned int Length,unsigned int width);
extern void displayHoursH(unsigned char NUM);
extern void displayHoursL(unsigned char NUM);
extern void displayMinuteH(unsigned char NUM);
extern void displayMinuteL(unsigned char NUM);
extern void displayColon(unsigned char cls);
extern void displayIcon_Bluetooth(unsigned char cls) ; //0x00清除 00xff显示
extern void displayIcon_Battery(unsigned char state,unsigned char cls);  //0x00清除 00xff显示 state 0empty 1 2 3full 4charging




#endif
