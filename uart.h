#ifndef uart_h
#define uart_h
#include "ez8_4k_XP.h"
#include "defines.h"
#include "delay.h"
#include "interrupts.h"

//uart device register address
#define uart 	0xF40
/*****************************
####@@ configurations  @@####
******************************/

// uart recieve interrupts
#define UART_R_INTERRUPTS 3  
//(1 low priority, 2 nominal, 3 high, comment to disable)

//uart transmit interrupts
//#define UART_T_INTERRUPTS 1 
//(1 low priority, 2 medium, 3 high, comment to disable)

//variables
char *receive_buffer;
extern int x;
unsigned int BRG0;

//UaRT configurations 
#define BAUDRATE 9600
#define	bits 8
#define stpbits one
#define	parity none

//uart device construct
void construct_uart(void);
//intialization
void init_uart(void);
//link layer
//void send(char *s_buffer);
//void receive(char *r_buffer);
void send(char data);
void receive(void);

char read(void);//link single byte test function 

extern void ISR_Receive(void);
#endif 
