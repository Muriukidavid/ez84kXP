#ifndef z8_4k_XP
#define z8_4k_XP
#include "generics.h"
//ez8 4k XP defines 
unsigned long int ez8_freq = 5529600; //the ez8 4K frequency

//type port
typedef struct {
	volatile REG addr;
	volatile REG control;
	volatile REG input;
	volatile REG output;
}*PORT;

//TYPE GPIO
typedef struct{
	PORT portA;
	PORT portB;
	PORT portC;
}GPIO;

typedef struct {
	volatile unsigned char 
	cen:1,
	refsell:1,
	refext:1,
	cont:1,
	anain:4;
}ADCCTL0;
	
typedef struct {
	volatile unsigned char
	refselh:1,
	almhst:1,
	almlst:1,
	almhen:1,
	almlen:1,
	bufmode:3;
}ADCCTL1;

//type adc
typedef struct {
	ADCCTL0 ctl0;
	ADCCTL1 ctl1;	
	volatile REG datah;	
	volatile REG datal;	
	volatile REG highthresh;	
	volatile REG adc_reserved;	
	volatile REG lowthresh;		
}*ADC;

typedef struct {
	volatile unsigned char 
	 rda:1, 
	  pe:1, 
	  oe:1,
	  fe:1,
	brkd:1,
	tdre:1,
	 txe:1,
	 cts:1;
}STATUS0;

typedef struct {
	volatile unsigned char 
	 status1_reserved:6, 
	 newfrm:1,
	 mprx:1;
}STATUS1;

//uart control 0 register
typedef struct {
	volatile unsigned char	
	ten:1,
	ren:1,
	ctse:1,
	pen:1,
	psel:1,
	sbrk:1,
	stopbits:1,
	lben:1;
}CONTROL0;


//uart
typedef struct {
	volatile REG data;// Tx and Rx point to same location => (char*) 0x00;
	STATUS0 status0;	
	CONTROL0 control0;
	volatile REG control1; 	
	STATUS1 status1;
	volatile REG addr_cmp;
	volatile REG baudh;
	volatile REG baudl;
}*UART;

typedef struct {
	volatile unsigned char 	
	reserved:1,
	t1enh:1,
	t0enh:1,
	u0renh:1,
	u0tenh:1,
	reserved2:2,
	adcenh:1;
}IRQ0ENH;

typedef struct {
	volatile unsigned char 
	reserved:1,
	t1enl:1,
	t0enl:1,
	u0renl:1,
	u0tenl:1,
	reserved2:2,
	adcenl:1;			
}IRQ0ENL;

typedef struct {
	volatile unsigned char 
	pa7venh:1,
	pa6cenh:1,
	pa5enh:1,
	pa4enh:1,
	pad3enh:1,
	pad2enh:1,
	pa1enh:1,
	pa0enh:1;			
}IRQ1ENH;

typedef struct {
	volatile unsigned char 
	pa7venl:1,
	pa6cenl:1,
	pa5enl:1,
	pa4enl:1,
	pa3enl:1,
	pa2enl:1,
	pa1enl:1,
	pa0enl:1;			
}IRQ1ENL;

typedef struct {
	volatile unsigned char 
	reserved:4,
	c3enh:1,
	c2enh:1,
	c1enh:1,
	c0enh:1;			
}IRQ2ENH;

typedef struct {
	volatile unsigned char 
	reserved:4,
	c3enl:1,
	c2enl:1,
	c1enl:1,
	c0enl:1;			
}IRQ2ENL;

//interrupt controller
typedef struct {
	volatile REG irq0;
	IRQ0ENH irq0enh;
	IRQ0ENL irq0enl;
	volatile REG irq1;
	IRQ1ENH irq1enh;
	IRQ1ENL irq1enl;
	volatile REG irq2;
	IRQ2ENH irq2enh;
	IRQ2ENL irq2enl;
	volatile REG reserved0;
	volatile REG reserved1;
	volatile REG reserved2;
	volatile REG reserved3;
	volatile REG irqes;
	volatile REG irqss;
	volatile REG irqctl;
}*INTERRUPT_CONTROLLER;

//main struct
typedef struct {
	GPIO gpio;
	INTERRUPT_CONTROLLER interrupt_c0;
	UART uart0;
	ADC adc0;	
} ez8XP4k;

static ez8XP4k ez8;
void construct_ez8(){
	;//functions for initialization of ez8XP4k have been moved to respective .h files, nothing to do here.
}
#endif 
