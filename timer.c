#include "timer.h"

void construct_timer(void){
	#ifdef timer0_ON
		ez8.timer0=(TIMER)timer00;
	#endif
	#ifdef timer1_ON
		ez8.timer1=(TIMER)timer01;
	#endif
}

void init_timers(void){
	#ifdef timer0_ON
		selectedTimer = ez8.timer0;
		currentTimer=0x00;
		timerMode = timer0_mode;
		init_timer();
	#endif
	#ifdef timer1_ON
		selectedTimer  = ez8.timer1;
		currentTimer=0x01;
		timerMode = timer1_mode;
		init_timer();
	#endif
}

void init_timer(void){
	selectedTimer->tctl1.ten = 0; //disable the timer
	//general timer settings
	//#prescale value.
	selectedTimer->tctl1.pres = prescale_value; //prescale value=0, clock divided by (2^0=1)
	//#initial logic level 
	selectedTimer->tctl1.tpol = 0; //set timer polarity output forced low when disabled, complement forced high
	//#Timer Output alternate function.
	//the starting count value
	selectedTimer->th.byte_reg=0x00;
	selectedTimer->tl.byte_reg=0x01;
	//the reload value
	selectedTimer->trh.byte_reg=0xD8;
	selectedTimer->trl.byte_reg=0x00;
	//Configure the timer for PWM mode.
	switch(timerMode){
		case one_shot:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0;
		break;
		case continuous:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x01;
		break;
		case counter:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x02;
		break;
		case comparator_counter:
			selectedTimer->tctl0.tmodehi=1;
			selectedTimer->tctl1.tmode=0x02;
		break;
		case pwm_single:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x03;
			set_PWM(50);//initial 50% duty cycle
		break;
		case pwm_dual:
			selectedTimer->tctl0.tmodehi=1;
			selectedTimer->tctl1.tmode=0x00;
			set_PWM(10);//initial 50% duty cycle
		break;
		case capture:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x04;
		break;
		case capture_restart:
			selectedTimer->tctl0.tmodehi=1;
			selectedTimer->tctl1.tmode=0x01;
		break;
		case compare:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x05;
		break;
		case gated:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x06;
		break;
		case capture_compare:
			selectedTimer->tctl0.tmodehi=0;
			selectedTimer->tctl1.tmode=0x07;
		break;
		default://pwm dual mode is the default mode if you pass mode>10
			selectedTimer->tctl0.tmodehi=1;
			selectedTimer->tctl1.tmode=0;
		break;
	}
	//Configure the associated GPIO port pin for the Timer Output alternate function.
	//Write to the Timer Control register to enable the timer and initiate counting.
	selectedTimer->tctl1.ten=1;
}

/*******************
	PWM functions
*******************/
void set_FREQ(unsigned long int freq){// 0 to 100%
	char timer=currentTimer;
	freq_data = ez8_freq/(prescale*freq);
	switch(timer){
		case 0x00:
			ez8.timer0->trh.byte_reg = (freq_data & 0xFF00)>>8;
			ez8.timer0->trl.byte_reg = (freq_data & 0x00FF); 
		break;
		case 0x01:
			ez8.timer1->trh.byte_reg = (freq_data & 0xFF00)>>8;
			ez8.timer1->trl.byte_reg = (freq_data & 0x00FF);
		break;
		default:
			ez8.timer0->trh.byte_reg = (freq_data & 0xFF00)>>8;
			ez8.timer0->trl.byte_reg = (freq_data & 0x00FF);
		break;
		}
}


//reading the reload value from the registers
// this had huge errors, reload defined as a constant RELOAD in timer.h
/*
void get_Reload(void){
	char timer=currentTimer;
	switch(timer){
		case 0x00:
			rel_high = ez8.timer0->trh.byte_reg;
			rel_high = rel_high<<8;
			rel_low	 = ez8.timer0->trl.byte_reg;
			TReload = (rel_high|rel_low);
		break;
		case 0x01:
			rel_high = ez8.timer1->trh.byte_reg;
			rel_high = rel_high<<8;
			rel_low	 = ez8.timer1->trl.byte_reg;
			TReload = (rel_high|rel_low);
		break;
		default:
			rel_high = ez8.timer0->trh.byte_reg;
			rel_high = rel_high<<8;
			rel_low	 = ez8.timer0->trl.byte_reg;
			TReload = (rel_high|rel_low);
		break;
		}
		
}
*/

//read the current pwm value from the registers
void get_PWM(void){
	char timer=currentTimer;
	switch(timer){
		case 0x00:
			PWM_high = ez8.timer0->pwmh.byte_reg;
			PWM_low	 = ez8.timer0->pwml.byte_reg;
			current_PWM = (PWM_high<<8)|((PWM_low<<8)>>8);
		break;
		case 0x01:
			PWM_high = ez8.timer1->pwmh.byte_reg;
			PWM_low	 = ez8.timer1->pwml.byte_reg;
			current_PWM = (PWM_high<<8)|((PWM_low<<8)>>8);
		break;
		default:
			PWM_high = ez8.timer0->pwmh.byte_reg;
			PWM_low	 = ez8.timer0->pwml.byte_reg;
			current_PWM = (PWM_high<<8)|((PWM_low<<8)>>8);
		break;
	}
}


void set_PWM(unsigned long int duty) {// 0 to 100%
	char timer=currentTimer;
	switch(timer){
		case 0x00:
			pwm_data = (duty * RELOAD) / 100;
			ez8.timer0->pwmh.byte_reg = (pwm_data & 0xFF00)>>8;
			ez8.timer0->pwml.byte_reg = (pwm_data & 0x00FF); 
		break;
		case 0x01:
			pwm_data = (duty * RELOAD) / 100;
			ez8.timer1->pwmh.byte_reg = (pwm_data & 0xFF00)>>8;
			ez8.timer1->pwml.byte_reg = (pwm_data & 0x00FF); 
		break;
		default:
			pwm_data = (duty * RELOAD) / 100;
			ez8.timer0->pwmh.byte_reg = (pwm_data & 0xFF00)>>8;
			ez8.timer0->pwml.byte_reg = (pwm_data & 0x00FF); 
		break;
	}

}

void get_percent(void){
	percentage = (current_PWM*100)/RELOAD;
}

//reducing the pwm duty by ...
void reduce_PWM(void){
	if(!percentage<=10){
		//reduce PWM duty by 10%;
		percentage = percentage-10;
		//set new cur_PWM
		set_PWM(percentage);
	}else{
	//set pwm to minimum value
		set_PWM(10);
	}
}

void increase_PWM(void){
	if(percentage>=90){
	//set pwm to maximum value
	set_PWM(90);
	}else{
		//increase PWM by 10%;
		percentage = percentage+10;
		//set new PWM
		set_PWM(percentage);
		}
}