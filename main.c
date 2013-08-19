#include "main.h"

//test variables
float y=62.53;// a float to write to lcd
char count=0;
int main(){
	DI();//disable interrupts or hell breaks loose during hardware config
	construct_system();//bind device addresses
	init_system();//init devices
	EI();//enable interrupts: we have UART_recieve
	
	
	lcd_contrast(0x42);
	clearram();
	//test lcd
		cursorxy(1,2);
		putstr((unsigned char*)"UoN Physics:");
		cursorxy(2,2);
		putstr((unsigned char*)"adc1:");
		putstr((unsigned char*)"      ");
		cursorxy(3,2);
		putstr((unsigned char*)"adc2:");
		putstr((unsigned char*)"      ");
		cursorxy(4,2);
		putstr((unsigned char*)"float:");
		//clear old value
		clear(4,8,5);
		//write new value
		cursorxy(4,8);
		putfloat(y);//print data from float
	
	while(1)
	{		
		display();
		for(count=0;count<9;count++){
			increase_PWM();
			delay_ms(100);
		}
		for(count=9;count>0;count--){
			reduce_PWM();
			delay_ms(100);
		}
	}
	return 0;
}

//construct device before initializing
void construct_system(){
	construct_gpio();//binding gpio
	construct_uart();//binding uart
	construct_adc();//binding adc regs
	construct_timer();
	construct_interrupts();//binding irq regs
	//construct_mymemory();
	//construct_watchdog();
	//construct_power();
}


void init_system(){
	init_gpio();//initialize gpio ports
	init_uart();//configure uart, check uart.h
	init_adc();//initialize ADC, check adc.h
	init_lcd();//init lcd
	init_timers();
	//init_watchdog();
	//init_power();
	//init_interrupts(); 
}

void display(void){
	delay_ms(200);//simple delay to make display steady
	select_input(ana2);
	//read_adc();//read the inputs
	clear(2,7,6);//clear old data
	cursorxy(2,7);//set cursor
	//putint((int)ADC_compensated,0x04);//print data from adc	
	
	delay_ms(200);//simple delay to make display steady
	select_input(ana7);
	//read_adc();//read the inputs
	clear(3,7,6);//clear old data
	cursorxy(3,7);//set cursor
	//putint((int)ADC_compensated,0x04);//print data from adc	
}
