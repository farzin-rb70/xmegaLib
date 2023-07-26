/*
 * IncFile1.h
 *
 * Created: 7/23/2023 4:41:43 PM
 *  Author: rezaei
 */ 


#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <util/delay.h>

extern "C"{
	#include "xmegaIO.h"
	#include "xmegaBasicTimer.h"
	};


#define delay(x) _delay_ms(x)

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef bool boolean;

#endif /* ARDUINO_H_ */