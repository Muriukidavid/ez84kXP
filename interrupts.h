#ifndef interrupt_h
#define interrupt_h

#include "ez8_4k_XP.h"
#include "uart.h"
#include "adc.h"
//interrupt vectors
//#define interrupt_vector (int*) 0x00
//interrupt vectors
/*#define  RESET     0
#define  WDT       1
#define  TRAP      2
#define  TIMER2    3
#define  TIMER1    4
#define  TIMER0    5
*/
#define  uart0_rx  6 // divide the int address by 2 then -1 e.g for ISR_Receive (uart0_rx) = 0x0E=14/2=7-1=6
#define  uart0_tx  7
//#define  I2C       8
//#define  SPI       9
#define  adc_vec   10 
/*
#define  P7AD      11
#define  P6AD      12
#define  P5AD      13
#define  P4AD      14
#define  P3AD      15
#define  P2AD      16
#define  P1AD      17
#define  P0AD      18
*/
//interrupt controller device registers starting address
#define interrupt_c 0xFC0

extern char data_available;//adc data flag
extern unsigned char VInHigh, VInLow;
void construct_interrupts(void);
void init_interrupts(void);
//global interrupt functions
void EI(void);
void DI(void);

//isr
intrinsic void SET_VECTOR(int vect,void (*hndlr)(void));
extern void receive(void);
extern void read_adc(void);
#endif 
