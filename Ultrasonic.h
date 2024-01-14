#ifndef Ultrasonic_H
#define Ultrasonic_H
#include "types.h"


uint32 Measure_distance(void);
void Ultrasonic_Inti(void);
void UART0_init(void);
void UART0_Transmitter(unsigned char data);
void printstring(char *str);

#endif
