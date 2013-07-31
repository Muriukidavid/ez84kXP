#include "gpio.h"

void construct_gpio(){
	//gpio bindings
	ez8.gpio.portA= (PORT)porta;
	ez8.gpio.portB= (PORT)portb;
	ez8.gpio.portC= (PORT)portc;
}

void init_gpio(void){
	//initialize ports... assumption: all registers are initially zero-filled
	ez8.gpio.portA->addr.byte_reg = 0x02;		//select alternate(AF) function for portA
	ez8.gpio.portA->control.bit_reg.bit4 = ON;	
	ez8.gpio.portA->control.bit_reg.bit5 = ON;//set PA4 and PA5 as AF (UART Rx and Tx respectively)	
	
	//initialize port C for LCD
	ez8.gpio.portC->addr.byte_reg = 0x01;	//select data direction
	ez8.gpio.portC->control.byte_reg = 0x00;	//all outputs
	ez8.gpio.portC->output.byte_reg = 0x00;	//initialize all outputs to low
	//ez8.gpio.portC->output.bit_reg.bit4=ON;// for debugging setting a bit
	//initialize port B for ADC
	ez8.gpio.portB->addr.byte_reg = 0x07;		//select alternate function set 1(ASF1) for portB
	ez8.gpio.portB->control.bit_reg.bit2 = ON;	//select PB2 as ASF1 = ADC input
}


//LCD pin toggle functions
/* Modify it to fit your schematic */
//SCK = PC7 ON
void SCK(void) { 
	ez8.gpio.portC->output.bit_reg.bit7=ON;
}
//CLR_SCK = PC7 OFF
void CLR_SCK(void) { 
	ez8.gpio.portC->output.bit_reg.bit7=OFF;
}

//DAT = PC0 ON
void DAT(void) {
	ez8.gpio.portC->output.bit_reg.bit0=ON;
}
//CLR_DAT = PC0 OFF
void CLR_DAT(void) {
	ez8.gpio.portC->output.bit_reg.bit0=OFF;
}

//DC = PC1 ON
void DC(void) {
	ez8.gpio.portC->output.bit_reg.bit1=ON;
}
//CLR_DC = PC1 OFF
void CLR_DC(void) {
	ez8.gpio.portC->output.bit_reg.bit1=OFF;
}

//CE = PC2 ON
void CE(void) {
	ez8.gpio.portC->output.bit_reg.bit2=ON;
}
//CLR_CE = PC2 OFF	
void CLR_CE(void) {
	ez8.gpio.portC->output.bit_reg.bit2=OFF;
}
//RES = PC3 ON	
void RES(void) { 
	ez8.gpio.portC->output.bit_reg.bit3=ON; 
}
//CLR_RES = PC3 OFF
void CLR_RES(void) { 
	ez8.gpio.portC->output.bit_reg.bit3=OFF; 
}