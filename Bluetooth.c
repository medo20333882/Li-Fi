#include "tm4c123gh6pm.h"
void HC05_init(void)
{
	SYSCTL_RCGCUART_R |= 0x20;
    SYSCTL_RCGCGPIO_R |= 0x10;
    UART5_CTL_R = 0;
    UART5_IBRD_R = 104;
    UART5_FBRD_R = 11;
    UART5_CC_R = 0;
    UART5_LCRH_R = 0x60;
    UART5_CTL_R = 0x301;
    GPIO_PORTE_DEN_R = 0x20;
    GPIO_PORTE_AFSEL_R = 0x20;
    GPIO_PORTE_AMSEL_R = 0;
    GPIO_PORTE_PCTL_R = 0x00100000;
}

void Bluetooth_Write(unsigned char data)  
{
    while((UART5_FR_R & (1<<5)) != 0);
    	UART5_DR_R = data;
}

void Bluetooth_Write_String(char *str)
{
  while(*str)
	Bluetooth_Write(*(str++));
}
