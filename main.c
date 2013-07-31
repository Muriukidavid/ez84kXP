#include "main.h"

//test variables
float y=62.53;// a float to write to lcd

int main(){

	DI();//disable interrupts or hell breaks loose during hardware config
	construct_ez8();//bind device addresses
	init_system();//init devices
	EI();//enable interrupts: we have UART_recieve
	
	lcd_contrast(0x42);
	clearram();
	//test lcd
		cursorxy(1,2);
		putstr((unsigned char*)("UoN Physics:"));
		cursorxy(2,2);
		putstr((unsigned char*)("int:"));
		cursorxy(3,2);
		putstr((unsigned char*)("float:"));
		//clear old value
		clear(3,8,5);
		//write new value
		cursorxy(3,8);
		putfloat(y);//print data from float
	
	while(1)
	{		
		display();
	}
	return 0;
}

//construct device before initializing
void construct_system(){
	construct_gpio();//binding gpio
	construct_uart();//binding uart
	construct_adc();//binding adc regs
	construct_mymemory();
	construct_watchdog();
	construct_interrupts();//binding irq regs
	ez8.power = (POWER_CONTROLLER)0xF80;
}


void init_system(){
	init_gpio();//initialize gpio ports
	init_uart();//configure uart, check uart.h
	init_adc();//initialize ADC, check adc.h
	init_lcd();//init lcd
	init_interrupts(); 
	init_watchdog();
	//power configurations for stop mode
	ez8.power->adc=ON;
	ez8.power->tram=OFF;
	ez8.power->temp=OFF;
}

void display(void){
	delay_ms(20);//simple delay to make display steady
	read_adc();//read the inputs
	clear(2,6,5);//clear old data
	cursorxy(2,6);//set cursor
	putint((int)ADC_compensated,0x04);//print data from adc	
}