#include "Ultrasonic.h"
#include "types.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "GPTM.h"

uint32 Measure_distance(){
    uint32 Falling_Egde, Rising_Edge;
	Timer1_Init();
    GPIO_PORTA_DATA_R&= ~(1<<4);
    Timer1_delay(10);
    setBit(GPIO_PORTA_DATA_R,4);
    Timer1_delay(10);
    clearBit(GPIO_PORTA_DATA_R,4);
    while(1){
    	TIMER0_ICR_R=4;
      	while((TIMER0_RIS_R & 4) == 0) ;
	  	if(GPIO_PORTB_DATA_R & (1<<6)){
            Falling_Egde = TIMER0_TAR_R;
            TIMER0_ICR_R= 4;
            while((TIMER0_RIS_R & 4) == 0);
            Rising_Edge = TIMER0_TAR_R;
            return (Rising_Edge - Falling_Egde);
		}
  	}
}


void Ultrasonic_Inti(){
	SYSCTL_RCGCGPIO_R |= (1<<0);
	while((SYSCTL_PRGPIO_R&(1<<0))==0);
    GPIO_PORTA_DIR_R |=(1<<4);
    GPIO_PORTA_DEN_R |=(1<<4);
	GPIO_PORTA_DIR_R &=~(1<<5);
	GPIO_PORTA_DIR_R &=~(1<<6);
	GPIO_PORTA_PUR_R|=(1<<5) |(1<<6);
    GPIO_PORTA_DEN_R |=(1<<5)|(1<<6);
	SYSCTL_RCGCGPIO_R |= (1<<1);
	while((SYSCTL_PRGPIO_R&(1<<1))==0);
	GPIO_PORTB_DIR_R &= ~0x40;
    GPIO_PORTB_DEN_R |= 0x40;
    GPIO_PORTB_AFSEL_R|= 0x40;
    GPIO_PORTB_PCTL_R |= 0x07000000;
}

void UART0_init(){
  SYSCTL_RCGCUART_R |= (1<<0);
  SYSCTL_RCGCGPIO_R |= (1<<0);
  GPIO_PORTA_AFSEL_R|=(1<<0) | (1<<1);
  GPIO_PORTA_PCTL_R |=(1<<0) | (1<<4);
  GPIO_PORTA_DEN_R  |=(1<<0) | (1<<1);
  
  UART0_CTL_R&= (~(1<<0)) & (~(1<<8)) & (~(1<<9));
  UART0_IBRD_R=104;
  UART0_FBRD_R=11;
  UART0_LCRH_R|=(0x3<<5);
  UART0_CC_R=0x0;
  UART0_CTL_R|= (1<<0) | (1<<8)| (1<<9);
}

void UART0_Transmitter(unsigned char data)  {
      while((UART0_FR_R&(1<<5)) !=0){}
        UART0_DR_R=data;
}

void printstring(char *str){
  while(*str)
    UART0_Transmitter(*(str++));
	
}