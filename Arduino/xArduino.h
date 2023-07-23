#ifndef ARDUINO_H_
#define ARDUINO_H_

#define _ATXMEGA128A_4U_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>





#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define abs(x)       ({ typeof (x) _x = (x); _x > 0 ? _x : -_x; })
#define sq(x)        ({ typeof (x) _x = (x); _x * _x; })
#define min(a,b)     ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b)     ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })
#define round(x)     ({ typeof (x) _x = (x); _x >= 0 ? (long)(_x + 0.5) : (long)(_x - 0.5); })
#define radians(deg) ((deg) * DEG_TO_RAD)
#define degrees(rad) ((rad) * RAD_TO_DEG)


#define interrupts() sei()
#define noInterrupts() cli()


#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

//#define bit(b) (1UL << (b))

#ifndef delay
#define delay(_time) _delay_ms(_time)
#endif


#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#endif /* ARDUINO_H_ */