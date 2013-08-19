#include "ez8_4k_XP.h"
#include "defines.h"
#include "devices.h"

#define timer0_ON 0
//#define timer1_ON 0 //timer 1 not used

enum timer_modes {
	one_shot,
	continuous,
	counter, 
	comparator_counter,
	pwm_single, 
	pwm_dual,
	capture, 
	capture_restart, 
	compare, 
	gated, 
	capture_compare
};
	
#define timer0_mode pwm_dual // only timer0 connected as PWM
//requirements for PWM dual output
#define prescale_value 0 //clock divided by 1(2^prescale_value)
#define polarity 0 //low when timer disabled


//#define timer1_mode pwm_single //timer1 not used
TIMER selectedTimer;
char currentTimer;
char timerMode;
unsigned long int TReload;
void construct_timer(void);
void init_timers(void);
void init_timer(void);
//pwm stuff
#define RELOAD (unsigned long int) 55296 //the pwm timer reload value
unsigned long int pwm_data=00000000; //holder for read pwm value
unsigned int holder, rel_high, rel_low; 
unsigned char high_read, low_read;
unsigned long int percentage, current_PWM, PWM_high, PWM_low, freq_data, pwmin ;
//unsigned long int clock_frequency  = ez8_freq;
unsigned long int frequency = 10000,ref=3;
unsigned char prescale = 1 ;
//PWM function prototypes
void set_FREQ(unsigned long int freq);
void get_PWM(void);
void set_PWM(unsigned long int duty);
void get_percent(void);
void reduce_PWM(void);
void increase_PWM(void);