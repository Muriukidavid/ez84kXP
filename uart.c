#include "uart.h"

void construct_uart(void){
	ez8.uart0=(UART)uart;
}

void init_uart(){
	#ifdef UART_R_INTERRUPTS 
	SET_VECTOR(uart0_rx, ISR_Receive); //defining ISR for receive
	#endif
	#ifdef UART_T_INTERRUPTS
	SET_VECTOR(uart0_tx, ISR_Transmit);
	#endif
	
	BRG0 = ez8_freq/BAUDRATE;
	BRG0 = BRG0/16;	

	ez8.uart0->control0.stopbits=stpbits;	//transmission stop bits
	ez8.uart0->control0.ten=ON;				//transmitter enable
	ez8.uart0->control0.ren=ON;				//receiver enable
	
	#ifdef UART_MULTIPROCESSOR
		//TBD - to be done**
	#else
	ez8.uart0->control1.byte_reg=0x00;		// multiprosessor mode config byte all disabled
	#endif
	
	//parity
	if(parity==none){
		ez8.uart0->control0.pen=0;
	}
	else{
		ez8.uart0->control0.pen=1;
		if(parity==even){
			ez8.uart0->control0.psel=0;
		}
		else{
			ez8.uart0->control0.psel=1;
		}
	}
	
	
	//write the baudrate in the registers
	ez8.uart0->baudh.byte_reg = (unsigned int)((BRG0 & 0xFF00)>>8);
	ez8.uart0->baudl.byte_reg = (unsigned int)((BRG0 & 0x00FF) & 0x00FF);
	
}

void init_meter(void){//addresses for slaves 
	;
}

void init_buffers(void){
	;
}

//link layer
//void send(char *s_buffer){
void send(char data){
	ez8.uart0->control0.ren=OFF;//disable receiver
	if(ez8.uart0->status0.tdre){//check if data register is empty
		ez8.uart0->data.byte_reg = data;//write a byte to the data register
	}else{
		delay_ms(2);//wait for transmission
		ez8.uart0->data.byte_reg = data;
		}
	ez8.uart0->control0.ren=ON;//reenable receiver
}

//void receive(char *r_buffer){
void receive(void){
	x = (int)(ez8.uart0->data.byte_reg);
	send(x);
}

char read(void){
	return ez8.uart0->data.byte_reg;
}

char get_bufferlen(char *buffer){
	return 0x00;
}
