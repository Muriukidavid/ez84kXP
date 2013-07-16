#ifndef interrupt_h
#define interrupt_h

#include "ez8_4k_XP.h"
//interrupt vectors
//#define interrupt_vector (int*) 0x00
//uart interrupt vectors
#define  uart0_rx  6 // divide the int address by 2 e.g for ISR_Receive (uart0_rx) = 0x0E
#define  uart0_tx  7

//interrupt binding
#define interrupt_c 0xFC0


void construct_interrupts(void);
void init_interrupts(void);
//global interrupt functions
void EI(void);
void DI(void);
/*
	intrinsic void EI(void);
	intrinsic void DI(void);
*/
//isr
intrinsic void SET_VECTOR(int vect,void (*hndlr)(void));

extern void receive(void);
#endif 
