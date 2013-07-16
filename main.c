#include "main.h"

extern char x;// single character holder for data

int main(){
	//initialization
	DI();//disable interrupts or hell breaks loose during hardware config
	construct_ez8();//currently nothing here, intended
	construct_interrupts();//binding irq regs
	init_interrupts();
	
	construct_gpio();//binding gpio
	construct_uart();//binding uart
	construct_adc();//binding adc regs
	init_gpio();//initialize gpio ports
	init_uart();//configure uart, currently 8bits, no parity, 1 stop bit (8-n-1) polling method
	init_adc();//initialize ADC, 2 modes: continu
	
	EI();
	
	while(1)
	{	//testing the serial link, echo back whatever was received
		//delay_ms(200);
		//if(ez8.uart0->status0.rda){//check if receive status bit is set
			//x = read();//read a single byte from the data register
			//send(x);//write same stuff to data register to transmit
		//}
		;
	}
	return 0;
}
