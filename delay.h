#ifndef DELAY_H
#define DELAY_H
//////////////////////////////////////////////
// note: approximation only 				//
//	not tested with other clock frequencies	//
//////////////////////////////////////////////
#define clock_freq	5529.600		//kHz

#define	delay_us(x)	{ unsigned int count2 = 0; count2 = (x)*(clock_freq / 14800); while(--count2) continue;	}
void delay_ms(unsigned int secs);
#endif	// end DELAY_H