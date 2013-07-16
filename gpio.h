#ifndef gpio_h
#define gpio_h
#include "ez8_4k_XP.h"
//gpio ports register addresses
#define porta 	0xFD0
#define portb 	0xFD4
#define portc 	0xFD8
void construct_gpio(void);
void init_gpio(void);
#endif 