#ifndef main_h
#define main_h
#include "ez8_4k_XP.h"
#include "interrupts.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "lcd.h"
#include "memory.h"
#include "watchdog.h"
//local variables

//external variables
//adc
volatile unsigned int ADC_compensated;
char data_available=0;
//uart

/******** functions **********/
void construct_ez8();
void init_system();
//application layer
void callibrate(char addr);
void diagnose(char addr);
void get_data(char addr);
void display(void);
//transport layer
char count_bytes(char *buffer);
char checksum(char *buffer);
void package(char *buffer);
void init_meter(void);//addresses for slaves 
void init_buffers(void);
char get_bufferlen(char *buffer);
extern char read(void);
extern void send(char data);
#endif 
