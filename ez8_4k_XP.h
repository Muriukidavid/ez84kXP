#ifndef z8_4k_XP
#define z8_4k_XP
#include "generics.h"
//ez8 4k XP defines 
unsigned long int ez8_freq = 5529600; //the ez8XP4K frequency

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
	bufmode2:1,
	bufmode1:1,
	bufmode0:1;
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

//timers
typedef struct {
	volatile unsigned char
	tmodehi:1,
	ticonfig:2,
	reserved:1,
	pwmd:3,
	incap:1;
}TCTL0;

typedef struct {
	volatile unsigned char
	ten:1,
	tpol:1,
	pres:3,
	tmode:3;
}TCTL1;

typedef struct {
	volatile REG th;//rststat; reset status as well as timer control
	volatile REG tl;
	volatile REG trh;
	volatile REG trl;
	volatile REG pwmh;
	volatile REG pwml;
	TCTL0 tctl0;
	TCTL1 tctl1;
}*TIMER;

//watchdog timer
typedef struct {
	volatile REG wdctl;//rststat; reset status as well as timer control
	volatile REG wdtu;
	volatile REG wdth;
	volatile REG wdtl;
}*WATCHDOG_TIMER;

//Flash Memory Controller
typedef struct{
	volatile REG fctl;//fstat; flash control as well as flash status same address
	volatile REG fps;//fprot; flash page select as well as flash sector protect same address
	volatile REG ffreqh;
	volatile REG ffreql;
}*FLASH_MEMORY_CONTROLLER;
//eZ8 CPU
typedef struct{
	volatile unsigned char 
	tram:1,
	reserved:2,
	vbo:1,
	temp:1,
	adc_p:1,// adc conflicts with adc address definition, rename to adc_p ;-)
	comp:1,
	reserved1:1;
}*POWER_CONTROLLER;

//eZ8 CPU
typedef struct {
	volatile REG flags;
	volatile REG rp;//register pointer
	volatile REG sph;//stack pointer high byte
	volatile REG spl;//stack pointer low byte
}*CPU;

//main struct
typedef struct {
	TIMER timer0; 
	TIMER timer1; 
	UART uart;
	ADC adc;	
	//POWER_CONTROLLER power;
//	LED_CONTROLLER led_cont; //TBD
//	OSCILLATOR_CONTROLLER osc_cont; //TBD
//	COMPARATOR0 comparator; //TBD
	INTERRUPT_CONTROLLER interrupt_c;
	GPIO gpio;
	//WATCHDOG_TIMER watchdog;
//	TRIM_BIT_CONTROLLER trim_bit_c; //TBD
	FLASH_MEMORY_CONTROLLER flash_mc;
	CPU cpu;
}ez8XP4k;

//instance
static ez8XP4k ez8;
#endif 
