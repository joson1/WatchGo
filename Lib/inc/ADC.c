#include "ADC.h"

unsigned int ADC=0;

void  ADCread();
{
    unsigned int R;
    unsigned int L;

    ADC=ADC_RES;
    ADC<<8;
    ADC|=ADC_RESL;
}

void ADC_Isr() interrupt 5
{
    ADCread();

}
