/*
 * xmegaBasicTimer.h
 *
 * Created: 5/27/2023 12:19:21 PM
 *  Author: rezaei
 */

#ifndef XMEGABASICTIMER_H_
#define XMEGABASICTIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>


#define TIM0 0
#define TIM1 1
#define TIM2 2
#define TIM3 3
#define TIM4 4

extern volatile unsigned long millisTimer;
void clockConfig(void);
void initTimer10Ms(uint8_t timerNumber);
void millisTimerConfig(void);
unsigned long millis(void);

#endif /* XMEGABASICTIMER_H_ */