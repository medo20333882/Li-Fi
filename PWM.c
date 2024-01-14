#include "tm4c123gh6pm.h"
void PWM_Config(void){
  /*
  SYSCTL_RCGCPWM_R|=(1<<0);
  SYSCTL_RCGCGPIO_R |=0x02;
  SYSCTL_RCC_R&=~(1<<20);
  GPIO_PORTB_AFSEL_R|=(1<<7);
  GPIO_PORTB_PCTL_R|= 0x40000000;
  GPIO_PORTB_DEN_R|=(1<<7);
*/
  SYSCTL_RCGCPWM_R|=(1<<1);
  SYSCTL_RCGCGPIO_R|=(1<<5);
  SYSCTL_RCC_R&=~(1<<20);
  GPIO_PORTF_AFSEL_R|=(1<<2);
  GPIO_PORTF_PCTL_R= 0x00000500;
  GPIO_PORTF_DEN_R|=(1<<2);

}


void PWM_Channel_config(void){
/*
  PWM0_1_CTL_R &=~(1<<0);
  PWM0_1_CTL_R &=~(1<<1);
  PWM0_1_LOAD_R =420;
  PWM0_1_CMPA_R=210;
  PWM0_1_GENA_R|=(1<<2)|(1<<3)|(1<<7);
  PWM0_1_CTL_R |=(1<<0);
  PWM0_ENABLE_R|=(1<<1);
*/

  PWM1_3_CTL_R&=~(1<<0);
  PWM1_3_CTL_R&=~(1<<1);
  PWM1_3_LOAD_R=400;
  PWM1_3_CMPA_R=200;
  PWM1_3_GENA_R|=(1<<2)|(1<<3)|(1<<7);
  PWM1_3_CTL_R |=(1<<0);
  PWM1_ENABLE_R|=(1<<6);
  }

