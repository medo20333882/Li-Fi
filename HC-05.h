#ifndef Bluetooth_H
#define Bluetooth_H
#include "types.h"

void HC05_init(void);
char Bluetooth_Read(void);
void Bluetooth_Write(unsigned char data); 
void Bluetooth_Write_String(char *str);


#endif
