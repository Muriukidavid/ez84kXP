#include "interrupts.h"
#include "defines.h"

void construct_interrupts(void){
	ez8.interrupt_c0 = (INTERRUPT_CONTROLLER)interrupt_c;
}
void init_interrupts(void){
	//ez8.interrupt_c0->irq0enh.u0renh=ON;
	#ifdef UART_R_INTERRUPTS
	if(UART_R_INTERRUPTS==3){
		ez8.interrupt_c0->irq0enh.u0renh=ON;//UART receive high priority interrups 
		ez8.interrupt_c0->irq0enl.u0renl=ON;
	}else if(UART_R_INTERRUPTS==2){
		ez8.interrupt_c0->irq0enh.u0renh=ON;//UART receive nominal priority interrups 
		ez8.interrupt_c0->irq0enl.u0renl=OFF;
	}else{
		ez8.interrupt_c0->irq0enh.u0renh=OFF;//UART receive low priority interrups 
		ez8.interrupt_c0->irq0enl.u0renl=ON;
		}
	#endif 
	#ifdef UART_T_INTERRUPTS
	if(UART_T_INTERRUPTS==3){
		ez8.interrupt_c0->irq0enh.u0tenh=ON;//UART transmit high priority interrups 
		ez8.interrupt_c0->irq0enl.u0tenl=ON;
	}else if(UART_T_INTERRUPTS==2){
		ez8.interrupt_c0->irq0enh.u0tenh=ON;//UART transmit nominal priority interrups 
		ez8.interrupt_c0->irq0enl.u0tenl=OFF;
	}else{
		ez8.interrupt_c0->irq0enh.u0tenh=OFF;//UART transmit low priority interrups 
		ez8.interrupt_c0->irq0enl.u0tenl=ON;
		}	
	#endif
	//adc interrupts
	#ifdef ADC_INTERRUPTS
		if(ADC_INTERRUPTS==3){
		ez8.interrupt_c0->irq0enh.adcenh=ON;
		ez8.interrupt_c0->irq0enl.adcenl=ON;
		}else if(ADC_INTERRUPTS==2){
			ez8.interrupt_c0->irq0enh.adcenh=ON;
			ez8.interrupt_c0->irq0enl.adcenl=OFF;
			}else{
				ez8.interrupt_c0->irq0enh.adcenh=OFF;
				ez8.interrupt_c0->irq0enl.adcenl=ON;
				}
	#endif
}
//global interrupt functions
void EI(void){
	asm("\t ei");
}
void DI(void){
	asm("\t di");
}
#ifdef UART_R_INTERRUPTS
#pragma interrupt // interupt service routine for receive 
void  ISR_Receive(void) {  
    receive();
}
#endif

#ifdef UART_T_INTERRUPTS
#pragma interrupt // interupt service routine for transmit 
void  ISR_Transmit(void) {  
    ;
}
#endif

#ifdef ADC_INTERRUPTS
#pragma interrupt//interrupt service routine for adc conversion
void isr_ADC(void){
	VInHigh=ez8.adc0->datah.byte_reg;
	VInLow=ez8.adc0->datal.byte_reg;
	data_available=1;
}
#endif
