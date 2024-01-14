#include "tm4c123gh6pm.h"
#include "Ultrasonic.h"
#include <stdio.h>
#include "Smoke.h"
#include "types.h"
#include "HC-05.h"
#include "GPTM.h"
#include "DIO.h"
#include "bitwise_operation.h"

volatile int run = 0;

int main(){
  uint32 time;
  uint32 distance;
  uint16 Analog_value;
  int8 mesg[20];
  
  DIOD_init();
  DIO_init();
  Ultrasonic_Inti();
  DIO_A_Interrupt_Setup();
  
  ADC_Intit();
  Sample_Sequencer();
  
  Timer0_Init();
  Timer2_Init();
  
  UART0_init();
  HC05_init();
  while(1){
	while(run == 0){};
	//Smoke Sensor Configuration
    ADC0_PSSI_R|=(1<<3);
    while((ADC0_RIS_R & 0x8)==0x0);
    Analog_value=ADC0_SSFIFO3_R;
    ADC0_ISC_R|=(1<<3);
    if(Analog_value > 2800){
	  	setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(100);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Timer2_delay(100);
		setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(100);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Timer2_delay(100);
		setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(100);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Bluetooth_Write_String("ELBET BYWLA33");
		GPIO_PORTF_DATA_R|=(1<<1);
        sprintf(mesg,"\r\nSmoke_Value = %d", Analog_value); 
        printstring(mesg);
    }
    else{
        GPIO_PORTF_DATA_R&=~(1<<1);
        sprintf(mesg,"\r\nSomke_Value = %d", Analog_value); 
        printstring(mesg);
		Timer2_delay(200);
    }
  //magnetic Config
    if ((GPIO_PORTD_DATA_R & (1<<1)) == (1<<1)){
	  	setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(200);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Timer2_delay(100);
		setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(200);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Bluetooth_Write_String("SEEB EL MAGENT");
		GPIO_PORTF_DATA_R|=(1<<2);
    }
   else{
        GPIO_PORTF_DATA_R&=~(1<<2);
	  	GPIO_PORTD_DATA_R&=~(1<<2);
		Timer2_delay(200);	
   }
  //Ultrasonic config
    time = Measure_distance(); 
    distance = (time * 10625)/10000000;  
    if(distance<30){
	  	setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(200);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Timer2_delay(200);
		setBit(GPIO_PORTD_DATA_R,2);
		Timer2_delay(100);
		GPIO_PORTD_DATA_R&=~(1<<2);
		Bluetooth_Write_String("EB3D EDAK");
		GPIO_PORTF_DATA_R|=(1<<3);
        sprintf(mesg, "\r\nDistance = %d cm", distance);
        printstring(mesg);
    }
	
    else {
        GPIO_PORTF_DATA_R&=~(1<<3);
	  	GPIO_PORTD_DATA_R&=~(1<<2);		
      	sprintf(mesg, "\r\nDistance = %d cm", distance);
      	printstring(mesg);
	  	Timer2_delay(200);
    }
  }
}

void GPIO_PortA_handler(){
  if((GPIO_PORTA_MIS_R&(1<<5))==(1<<5)){
	run=0;
  	GPIO_PORTA_ICR_R |= (1<<5);
  }
  else if ((GPIO_PORTA_MIS_R&(1<<6))==(1<<6)){
    GPIO_PORTA_ICR_R |= (1<<6);
	run=1;
  }
}