#include "interrupts.h"
#include "defines.h"

void construct_interrupts(void){
	ez8.interrupt_c0 = (INTERRUPT_CONTROLLER)interrupt_c;
}
void init_interrupts(void){
	ez8.interrupt_c0->irq0enh.u0renh=ON;//UART receive high priority interrups Rx only interrupts 
	ez8.interrupt_c0->irq0enl.u0renl=ON;
	ez8.interrupt_c0->irq0enh.u0tenh=OFF;	//transmit interrupts are off/ no need for priority
	ez8.interrupt_c0->irq0enl.u0tenl=OFF;	// 00 = priority low	
}
//global interrupt functions
void EI(void){
	asm("\t ei");
}
void DI(void){
	asm("\t di");
}

//isr
/*
void SET_VECTOR(int vect,void (*hndlr)(void)){
	*(interrupt_vector+vect)= (int)hndlr;
}
*/

#pragma interrupt // interupt service routine for receive 
void  ISR_Receive(void) {  
	//SET_VECTOR(uart0_rx, ISR_Receive); //defining ISR for receive
    receive();
}	
#pragma interrupt // interupt service routine for transmit 
void  ISR_Transmit(void) {  
    ;
}
