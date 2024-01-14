#ifndef DIO_H
#define DIO_H
#include "types.h"

void DIOD_init(void);
void DIO_init(void);
void DIO_WritePort(ulong32_ptr port,ulong32 value);
void DIO_WritePin(ulong32_ptr port,uint16 pin,uint16 value);
uint8 DIO_ReadPin(ulong32_ptr port,uint8 pin);
uint32 DIO_ReadPort(ulong32_ptr port);
void DIO_A_Interrupt_Setup(void);
#endif