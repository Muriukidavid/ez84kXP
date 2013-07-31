#ifndef ADC_H
#define ADC_H
#include "ez8_4k_XP.h"
#include "defines.h"
#include "interrupts.h"

#define adc 0xF70 		//adc device starting address
//configuration parameters
#define CONTINUOUS 1 	//comment this out if singleshot is needed
//#define BUFFERED 1		//comment this out if unbuffered is needed
//#define DIFFERENTIAL 1	//comment this out if single shot is needed
//#define GAIN20X 1		//comment this out for unity gain
#define INTERNAL_REF 3	//internal reference 1 for 1v, 2 for 2.0v, 3 for 2.2v, 
						//comment it out for no internal reference
#define ADC_INTERRUPTS 3//whether to use adc interrupts comment this for polled
//select inputs
enum adc_inputs {PBO=0,PB1,PB2, PB3,PB4,PB5,PB6,PB7};

#define INPUT PB2 // or PB pins to enable, e.g PB0|PB1|PB2 for the three pins as inputs
//calibration parameters
unsigned int ADC_gainCal, ADC_offset, ADC_gain, ADC_product;
extern volatile unsigned int ADC_compensated;
unsigned char VInHigh, VInLow;

void construct_adc(void);
void init_adc(void);
void callibrate_adc (void);
void compansate_adc(void);
void read_adc(void);

extern void isr_ADC(void);
#endif 
