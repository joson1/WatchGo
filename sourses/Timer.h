#ifndef __TIMER_H
#define __TIMER_H


extern unsigned int xdata TickCount;  //tickcount =500 is 1s
extern unsigned int xdata Hour;
extern unsigned int xdata Minute;
extern unsigned int xdata Second;
extern bit isHourChange;
extern bit isMinuteChange;
extern bit isSecondChange;
extern unsigned int xdata preHourH;
extern unsigned int xdata preMinuteH;


extern void Timer0Init(void);
#endif
