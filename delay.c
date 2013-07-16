#include "delay.h"

void delay_ms(unsigned int secs)
{
	while(--secs)
		delay_us(999);
}
