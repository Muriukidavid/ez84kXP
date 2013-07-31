//#include<math.h>
#include "ez8_4k_XP.h"
#include "defines.h"
#include "delay.h"
//pin operation functions
extern void SCK(void);
extern void CLR_SCK(void);
extern void DAT(void);
extern void CLR_DAT(void);
extern void DC(void);
extern void CLR_DC(void);
extern void CE(void);	
extern void CLR_CE(void);
extern void RES(void);
extern void CLR_RES(void);
//other functions
void spisend(unsigned char);
void init_lcd(void);
void wrdata(unsigned char);
void wrcmd(unsigned char);
void pixelxy(unsigned char, unsigned char);
void cursorxy(unsigned char, unsigned char);
void lcd_contrast(unsigned char contrast);
void clearram(void);
void putchar_1(unsigned char ch);
void putnibble(char nibble);
void putint(int in, char digits);
void putfloat(float in);
void putstr (unsigned char*);
int pow(int x,char y);
void clear(char x, char y, char xters);