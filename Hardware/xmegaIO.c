#include "xmegaIO.h"

#ifdef _ATXMEGA128A_1U_

PORT_t *regs[] = {
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTF,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTH,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTJ,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTK,
	(PORT_t *)&PORTQ,
	(PORT_t *)&PORTQ,
	(PORT_t *)&PORTQ,
	(PORT_t *)&PORTQ,
	(PORT_t *)&PORTR,
	(PORT_t *)&PORTR,
};
const uint8_t bitNum[] =
{0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3,
0, 1};

#endif

#ifdef _ATXMEGA128A_4U_
PORT_t *regs[] = {
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTA,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTB,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTC,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTD,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTE,
	(PORT_t *)&PORTR,
	(PORT_t *)&PORTR,
};
const uint8_t bitNum[] =
{0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3,
0, 1};
#endif



void pinMode(uint8_t pin, uint8_t mode)
{
	if (mode == INPUT)
	{
		regs[pin]->DIRSET &= ~_BV(bitNum[pin]);
		*(((uint8_t *)&regs[pin]->PIN0CTRL) + bitNum[pin]) |= PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;
	}
	else if (mode == INPUT_PULLUP)
	{
		regs[pin]->DIRSET &= ~_BV(bitNum[pin]);
		*(((uint8_t *)&regs[pin]->PIN0CTRL) + bitNum[pin]) |= PORT_OPC_PULLUP_gc | PORT_ISC_LEVEL_gc;
	}
	else if (mode == OUTPUT)
	{
		regs[pin]->DIRSET |= _BV(bitNum[pin]);
		*(((uint8_t *)(&(regs[pin]->PIN0CTRL))) + bitNum[pin]) |= PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;
	}
	else if (mode == OUTPUT_PULLUP)
	{
		regs[pin]->DIRSET |= _BV(bitNum[pin]);
		*(((uint8_t *)&regs[pin]->PIN0CTRL) + bitNum[pin]) |= PORT_OPC_PULLUP_gc | PORT_ISC_LEVEL_gc;
	}
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	if (!val)
	{
		regs[pin]->OUTCLR = _BV(bitNum[pin]);
	}
	else
	{
		regs[pin]->OUTSET = _BV(bitNum[pin]);
	}
}

int digitalRead(uint8_t pin)
{
	return bitRead(regs[pin]->IN,bitNum[pin]);
}
