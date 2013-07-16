#include "gpio.h"
#include "defines.h"

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
	
	//initialize port B for ADC
	ez8.gpio.portB->addr.byte_reg = 0x07;		//select alternate function set 1(ASF1) for portB
	ez8.gpio.portB->control.bit_reg.bit4 = ON;	//select PB4 as ASF1 = ADC input
}