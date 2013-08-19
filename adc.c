#include "adc.h"

void construct_adc(void){
	ez8.adc=(ADC)adc0;
}

void init_adc(void){
	#ifdef ADC_INTERRUPTS
	SET_VECTOR(adc_vec, isr_ADC);
	#endif
	ez8.adc->ctl1.refselh=OFF;//reset default value of this bit
	/* Input Buffer Mode Select: BUFMODE[2:0] 
	 000 = Single-ended, unbuffered input
	 001 = Single-ended, buffered input with unity gain
	 100 = Differential, unbuffered input
	 101 = Differential, buffered input with unity gain
	 111 = Differential, buffered input with 20x gain
	*/
	#ifdef DIFFERENTIAL
	 ez8.adc->ctl1.bufmode2=ON;
	#else
	 ez8.adc->ctl1.bufmode2=OFF;
	#endif
	
	#ifdef BUFFERED
	 ez8.adc->ctl1.bufmode0=ON;
	#else 
	 ez8.adc->ctl1.bufmode0=OFF;
	#endif
	
	#ifdef GAIN2X
	 ez8.adc->ctl1.bufmode1=ON;
	#else
	 ez8.adc->ctl1.bufmode1=OFF;
	#endif 
	
	/* internal reference: {refselh,refsell}
	 00 = internal reference disabled
	 01 = internal reference = 1.0V
	 10 = internal reference = 2.0V
	 11 = internal reference = 2.2V
	*/
	#ifdef INTERNAL_REF
	 if(INTERNAL_REF==1){
		ez8.adc->ctl0.refsell=ON; 
		}else if(INTERNAL_REF==2){
			ez8.adc->ctl1.refselh=ON;
			ez8.adc->ctl0.refsell=OFF;
			}else if(INTERNAL_REF==3){
				ez8.adc->ctl1.refselh=ON;
				ez8.adc->ctl0.refsell=ON;
				}
	 ez8.adc->ctl0.refext=OFF; //no external ref, pin available for I/O	
	#else
	 ez8.adc->ctl1.refselh=OFF;
	 ez8.adc->ctl0.refsell=OFF;
	 ez8.adc->ctl0.refext=ON; //external reference to a pin	
	#endif
	
 
	/*Analog Input Select:ADCCTL0 ANAIN[3:0]*/
	ez8.adc->ctl0.anain = ana2; 	
	//Continuous Conversion/Single shot Mode selection
	#ifdef CONTINUOUS
	ez8.adc->ctl0.cont=ON; 	
	#endif 
	ez8.adc->ctl0.cen=ON;
}

void select_input(char channel){
	ez8.adc->ctl0.anain = channel; 
}

//software ADC calibration
void callibrate_adc (void){
	rom unsigned char *ptr;
	ADC_gainCal = 0;
	//ez8.flash_mc0->fps.bit_reg.bit7=ON;//FPS = 0x80; // Enable access information area. set bit 7
	ptr = (rom unsigned char*)(0xFFE9); //offset correction byte
	ADC_offset = *ptr;
	ptr = (rom unsigned char*)(0xFFEA); //ADC_gain_hi_byte
	ADC_gain = *ptr;
	ADC_gain = ADC_gain <<8;
	ptr = (rom unsigned char*) (0xFFEB); //ADC_gain_lo_byte
	ADC_gain |= *ptr;
	ADC_gainCal = ADC_gain;
	//ez8.flash_mc0->fps.bit_reg.bit7=OFF;//FPS = 0x00; //close information area
}

void read_adc(void){
	#ifndef ADC_INTERRUPTS //blocking polled adc read
	ez8.adc->ctl0.cen=ON;
	while(ez8.adc->ctl0.cen==1){
		asm("nop");
		}
	VInHigh=ez8.adc->datah.byte_reg;
	VInLow=ez8.adc->datal.byte_reg;
	ADC_data = (VInHigh <<8)| (VInLow); //ADC output word
	ADC_data = (ADC_data >> 3) & 0xFFF;
	ADC_compensated=(int)(ADC_data);
	#else //non-blocking wait for interrupts
		if(data_available){//check if from ISR
			ADC_data = (VInHigh <<8)| (VInLow); //ADC output word
			ADC_data = (ADC_data >> 3) & 0xFFF;
			ADC_compensated=(int)(ADC_data);
			data_available=0;
		}
		ez8.adc->ctl0.cen=ON;
	#endif
}

void compansate_adc(void){
	if ((ADC_offset & 0x80) == 0x80){
		ADC_offset = ~ADC_offset + 1;
		ADC_data = ADC_data + ADC_offset;
	}
	else{
		ADC_data = ADC_data - ADC_offset;
	}
	ADC_product = ADC_data * ADC_gainCal;
	ADC_product = (ADC_product + 0x8000)>> 16;
	ADC_compensated = ((ADC_data + ADC_product)>>2)&0x03FF;
}
