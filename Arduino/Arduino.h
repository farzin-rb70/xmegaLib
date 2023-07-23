/*
 * IncFile1.h
 *
 * Created: 7/23/2023 4:41:43 PM
 *  Author: rezaei
 */ 


#ifndef ARDUINO_H_
#define ARDUINO_H_


extern "C"{
	#include "xmegaIO.h"
	#include "xmegaBasicTimer.h"
	};



#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#endif /* ARDUINO_H_ */