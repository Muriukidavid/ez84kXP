#include "watchdog.h"

void construct_watchdog(void){
	ez8.watchdog0 = (WATCHDOG_TIMER)watchdog;
}

void init_watchdog(void){
	//unlock wdt
	ez8.watchdog0->wdctl=0x55;
	ez8.watchdog0->wdctl=0xAA;
	//reload value =300ms
	ez8.watchdog0->wdtu=0x00;
	ez8.watchdog0->wdth=0x01;
	ez8.watchdog0->wdtl=0x2C;
}