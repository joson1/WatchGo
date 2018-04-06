#ifndef __POWER_H
#define __POWER_H

//AXP173电源管理芯片

#include "ONboard_IIC.h"

extern unsigned char xdata powerStat;


extern void powerInit();
extern void getBatteryState();


#endif
