#ifndef bitwise_operation_h
#define bitwise_operation_h

#define setBit(Register, Bit) (Register |= (1 << Bit))
#define clearBit(Register, Bit) (Register &= ~(1 << Bit))
#define getBit(Register, Bit) (Register & (1<<Bit))
#define toggleBit(Register, Bit) (Register ^= (1 << Bit))

#endif
