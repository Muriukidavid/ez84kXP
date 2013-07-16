#ifndef main_h
#define main_h
#include "interrupts.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"


/*typedef struct {
	char 
	en:1,
	reserved:7;
} *irq;
irq irq0=(irq)0xFCF;
*/

//#include "defines.h"
//#include "lcd.h"
//application layer
void callibrate(char addr);
void diagnose(char addr);
void get_data(char addr);
//transport layer
char count_bytes(char *buffer);
char checksum(char *buffer);
void package(char *buffer);
void init_meter(void);//addresses for slaves 
void init_buffers(void);
char get_bufferlen(char *buffer);
extern char read(void);
extern void send(char data);
#define Stack (*(int*)0xffe)
#endif 
