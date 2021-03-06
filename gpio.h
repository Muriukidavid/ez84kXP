#ifndef gpio_h
#define gpio_h
#include "ez8_4k_XP.h"
#include "defines.h"
#include "devices.h"

void construct_gpio(void);
void init_gpio(void);

//lcd pin toggle prototypes
void SCK(void);
void CLR_SCK(void);
void DAT(void);
void CLR_DAT(void);
void DC(void);
void CLR_DC(void);
void CE(void);	
void CLR_CE(void);
void RES(void);
void CLR_RES(void);
#endif 