#ifndef generics_h
#define generics_h
typedef struct {
	volatile unsigned char bit7:1;
	volatile unsigned char bit6:1; 
	volatile unsigned char bit5:1; 
	volatile unsigned char bit4:1; 
	volatile unsigned char bit3:1; 
	volatile unsigned char bit2:1; 
	volatile unsigned char bit1:1; 
	volatile unsigned char bit0:1;
}bitreg;
typedef union {
	bitreg bit_reg;
	char byte_reg; 
} REG;
#endif 