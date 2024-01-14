#include "Smoke.h"
#include "tm4c123gh6pm.h"
#include "types.h"
void ADC_Intit(){
  SYSCTL_RCGCADC_R|=(1<<0);
  SYSCTL_RCGCGPIO_R|=0x10;
  while((SYSCTL_PRGPIO_R&0x10) == 0);
  GPIO_PORTE_AFSEL_R |=(1<<3);
  GPIO_PORTE_DEN_R&= ~(1<<3);
  GPIO_PORTE_AMSEL_R |=(1<<3);
}

void Sample_Sequencer(){
  ADC0_ACTSS_R &=~(1<<3);  
  ADC0_EMUX_R &=(~(0xF000));
  ADC0_SSMUX3_R=0x0;
  ADC0_SSCTL3_R|=(1<<1)|(1<<2);
  ADC0_ACTSS_R |=(1<<3); 
}