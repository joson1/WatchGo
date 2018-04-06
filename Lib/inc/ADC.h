#ifndef __ADC_H
#define __ADC_H

#define ADCFormatLeft 0x00
#define ADCFormatRight 0x20


#define ADC_powerON(CHS) ADC_CONTR=(0x90|=CHS)
#define ADC_Start() ADC_CONTR|=0x40;EADC=1;EA=1
    //XȡֵΪ0-16 
#define ADC_setSpeed(X) ADCCFG|=X


extern unsigned int ADC;

extern void ADCread();

#endif
