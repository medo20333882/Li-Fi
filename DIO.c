#include "types.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include  "DIO.h"

void DIO_A_Interrupt_Setup() {
	GPIO_PORTA_DIR_R &=~(1<<6);
	GPIO_PORTA_DIR_R &=~(1<<5);
    GPIO_PORTA_DEN_R |= (1<<5)|(1<<6);
    GPIO_PORTA_PUR_R |= (1<<5)|(1<<6);
	
    GPIO_PORTA_IS_R &=~(1<<5); 	//interrupt sense edge Trigger
	GPIO_PORTA_IS_R &=~(1<<6);	
    GPIO_PORTA_IBE_R &= ~(1<<5);//DISABLE both edges interrupt
	GPIO_PORTA_IBE_R &= ~(1<<6);
    GPIO_PORTA_IEV_R &= ~(1<<5);//AT falling edge only
    GPIO_PORTA_IEV_R &= ~(1<<6);
    GPIO_PORTA_IM_R |= (1<<5)|(1<<6);	// not masked
    GPIO_PORTA_ICR_R |= (1<<5)|(1<<6);	// clearing Flag
    NVIC_EN0_R = 0x00000001;
}

void DIO_init(void){
  SYSCTL_RCGCGPIO_R |= 0x00000020; //Intialize PORTF
  while((SYSCTL_PRGPIO_R&0x00000020) == 0); 
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = 0x1F;
  GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_PUR_R = 0x11;
  GPIO_PORTF_DEN_R = 0x1F;
}

void DIOD_init(void){
  SYSCTL_RCGCGPIO_R|=0x08; // intializing PORTD
  while((SYSCTL_PRGPIO_R&0x08) == 0){};
  GPIO_PORTD_DIR_R&=~(1<<1);
  GPIO_PORTD_PUR_R|=(1<<1);
  GPIO_PORTD_DEN_R|=(1<<1);
  GPIO_PORTD_CR_R |=(1<<2);
  GPIO_PORTD_DIR_R|=(1<<2);
  GPIO_PORTD_DEN_R|=(1<<2);
}
void DIO_WritePort(ulong32_ptr port,ulong32 value)
{
  *port = value;
}

void DIO_WritePin(ulong32_ptr port,uint16 pin,uint16 value)
{
  *port &= (value << pin);
  if(value == 1)
  {
    setBit(*port , pin);
  }
  else if (value == 0)
  {
    clearBit(*port, pin);
  }
  
}

uint8 DIO_ReadPin(ulong32_ptr port,uint8 pin)
{
  return getBit(*port,pin);
}

uint32 DIO_ReadPort(ulong32_ptr port)
{
  return *(port);
}



