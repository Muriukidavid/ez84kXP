#include"interrupts.h"

void construct_interrupts(void){
	ez8.interrupt_c0 = (INTERRUPT_CONTROLLER)interrupt_c;
}
void init_interrupts(void){
	;
}
//global interrupt functions
void EI(void){
	asm("\t ei");
	//ez8.interrupt_c0->irqctl.bit_reg.bit7=1;//write 0 to bit7 of IRQCTL
}
void DI(void){
	asm("\t di");
	//ez8.interrupt_c0->irqctl.bit_reg.bit7=0;
}

//isr
void SET_VECTOR(int vect,void (*hndlr)(void)){
	*(interrupt_vector+vect)= (int)hndlr;
}

#pragma interrupt // interupt service routine for receive 
void  ISR_Receive(void) {  
	//SET_VECTOR(uart0_rx, ISR_Receive); //defining ISR for receive
    receive();
}	
#pragma interrupt // interupt service routine for transmit 
void  ISR_Transmit(void) {  
    ;
}
