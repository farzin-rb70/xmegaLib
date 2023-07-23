#ifndef XMEGA_H_
#define XMEGA_H_

/*#include "Arduino.h"*/
#include <stdint.h>
#include <avr/io.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define OUTPUT_PULLUP 0x3

#ifdef _ATXMEGA128A_1U_ 
#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 8
#define PB1 9
#define PB2 10
#define PB3 11
#define PB4 12
#define PB5 13
#define PB6 14
#define PB7 15

#define PC0 16
#define PC1 17
#define PC2 18
#define PC3 19
#define PC4 20
#define PC5 21
#define PC6 22
#define PC7 23

#define PD0 24
#define PD1 25
#define PD2 26
#define PD3 27
#define PD4 28
#define PD5 29
#define PD6 30
#define PD7 31

#define PE0 32
#define PE1 33
#define PE2 34
#define PE3 35
#define PE4 36
#define PE5 37
#define PE6 38
#define PE7 39

#define PF0 40
#define PF1 41
#define PF2 42
#define PF3 43
#define PF4 44
#define PF5 45
#define PF6 46
#define PF7 47

#define PH0 48
#define PH1 49
#define PH2 50
#define PH3 51
#define PH4 52
#define PH5 53
#define PH6 54
#define PH7 55

#define PJ0 56
#define PJ1 57
#define PJ2 58
#define PJ3 59
#define PJ4 60
#define PJ5 61
#define PJ6 62
#define PJ7 63

#define PK0 64
#define PK1 65
#define PK2 66
#define PK3 67
#define PK4 68
#define PK5 69
#define PK6 70
#define PK7 71

#define PQ0 72
#define PQ1 73
#define PQ2 74
#define PQ3 75

#define PR0 76
#define PR1 77

#endif

#ifdef _ATXMEGA128A_4U_

#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 8
#define PB1 9
#define PB2 10
#define PB3 11

#define PC0 12
#define PC1 13
#define PC2 14
#define PC3 15
#define PC4 16
#define PC5 17
#define PC6 18
#define PC7 19

#define PD0 20
#define PD1 21
#define PD2 22
#define PD3 23
#define PD4 24
#define PD5 25
#define PD6 26
#define PD7 27

#define PE0 28
#define PE1 29
#define PE2 30
#define PE3 31

#define PR0 32
#define PR1 33

#endif



#define NOT_A_PORT 0
#ifndef PROGMEM
#define PROGMEM __attribute__((__progmem__))
#endif

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif


#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

#endif /* XMEGA_H_ */