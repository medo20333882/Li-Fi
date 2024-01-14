#include "Ultrasonic.h"
#include "types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"

void Timer0_Init(){
    SYSCTL_RCGCTIMER_R|=0x01;
    TIMER0_CTL_R &= ~1;
    TIMER0_CFG_R = 4;
    TIMER0_TAMR_R=0x17;
    TIMER0_CTL_R |=0x0C;
    TIMER0_CTL_R |= (1<<0);
}

void Timer1_Init(){
    SYSCTL_RCGCTIMER_R |=(1<<1);     
    TIMER1_CTL_R = 0;            
    TIMER1_CFG_R = 0x04;         
    TIMER1_TAMR_R = 0x02;        
	TIMER1_CTL_R |= (1<<1);       
    TIMER1_CTL_R |= (1<<0);       
}
void Timer1_delay(uint32 time){
  //Micro_seconds delay Function
     TIMER1_CTL_R = 0;            
	 TIMER1_TAILR_R = ((time * 16000000)/1000000) - 1;  
     TIMER1_ICR_R = 0x1;
	 TIMER1_CTL_R |= (1<<1);       
     TIMER1_CTL_R |= (1<<0);       
     while ((TIMER1_RIS_R & 0x1) == 0);
}
void Timer2_Init(){
	 SYSCTL_RCGCTIMER_R |=(1<<2);
	 TIMER2_CFG_R=0x00;
	 TIMER2_TAMR_R=0x02;
	 TIMER2_CTL_R |= (1<<1);       
     TIMER2_CTL_R |= (1<<0); 
}
void Timer2_delay(uint32 time){
  //Milli_seconds delay Function
     TIMER2_CTL_R = 0;            
	 TIMER2_TAILR_R = (16000 * time)-1;  
     TIMER2_ICR_R = 0x1;
	 TIMER2_CTL_R |= (1<<1);       
     TIMER2_CTL_R |= (1<<0);       
     while ((TIMER2_RIS_R & 0x1) == 0);
}