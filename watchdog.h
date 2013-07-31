#ifndef watchdog_h
#define watchdog_h
#include "ez8_4k_XP.h"

#define watchdog 0xFF0

void construct_watchdog(void);
void init_watchdog(void);
#endif 