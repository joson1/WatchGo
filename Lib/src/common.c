#include "common.h"

void Delayus(unsigned int us )
{
    unsigned int i;
    for(i=MAIN_Fosc*us/12000;i>0;i--)
    {
        _nop_();
    }
}


void Delay5us()
{
    unsigned char i;

	_nop_();
	_nop_();
	i = 27;
	while (--i);
}
void Delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}

