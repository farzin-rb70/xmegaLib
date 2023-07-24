/*
 * ST7565Lcd.cpp
 *
 * Created: 7/24/2023 1:40:04 PM
 *  Author: rezaei
 */ 
#include "ST7565Lcd.h"
#include <util/delay.h>

#define DISPLAY_CLK_CONFIG()       {PORTD.DIRSET=PIN7_bm; PORTD.PIN7CTRL=PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;}
#define DISPLAY_CLK_SET()           {PORTD.OUTSET=PIN7_bm;}
#define DISPLAY_CLK_RESET()          {PORTD.OUTCLR=PIN7_bm;}

#define DISPLAY_DATA_CONFIG()       {PORTD.DIRSET=PIN5_bm; PORTD.PIN5CTRL=PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;}
#define DISPLAY_DATA_SET()           {PORTD.OUTSET=PIN5_bm;}
#define DISPLAY_DATA_RESET()          {PORTD.OUTCLR=PIN5_bm;}

#define DISPLAY_CS_CONFIG()       {PORTD.DIRSET=PIN4_bm; PORTD.PIN4CTRL=PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;}
#define DISPLAY_CS_SET()           {PORTD.OUTSET=PIN4_bm;}
#define DISPLAY_CS_RESET()          {PORTD.OUTCLR=PIN4_bm;}

#define DISPLAY_DS_CONFIG()       {PORTD.DIRSET=PIN1_bm; PORTD.PIN1CTRL=PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;}
#define DISPLAY_DS_SET()           {PORTD.OUTSET=PIN1_bm;}
#define DISPLAY_DS_RESET()          {PORTD.OUTCLR=PIN1_bm;}

#define DISPLAY_RESET_CONFIG()       {PORTD.DIRSET=PIN0_bm; PORTD.PIN0CTRL=PORT_OPC_PULLDOWN_gc | PORT_ISC_LEVEL_gc;}
#define DISPLAY_RESET_SET()           {PORTD.OUTSET=PIN0_bm;}
#define DISPLAY_RESET_RESET()          {PORTD.OUTCLR=PIN0_bm;}
	
#define P_CPU_NS (1000000000UL / F_CPU)

uint8_t avr_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t cycles;

	switch(msg)
	{
		case U8X8_MSG_DELAY_NANO:     // delay arg_int * 1 nano second
		// At 20Mhz, each cycle is 50ns, the call itself is slower.
		break;
		case U8X8_MSG_DELAY_100NANO:    // delay arg_int * 100 nano seconds
		// Approximate best case values...
		#define CALL_CYCLES 26UL
		#define CALC_CYCLES 4UL
		#define RETURN_CYCLES 4UL
		#define CYCLES_PER_LOOP 4UL

		cycles = (100UL * arg_int) / (P_CPU_NS * CYCLES_PER_LOOP);

		if(cycles > CALL_CYCLES + RETURN_CYCLES + CALC_CYCLES)
		break;

		__asm__ __volatile__ (
		"1: sbiw %0,1" "\n\t" // 2 cycles
		"brne 1b" : "=w" (cycles) : "0" (cycles) // 2 cycles
		);
		break;
		case U8X8_MSG_DELAY_10MICRO:    // delay arg_int * 10 micro seconds
		for(int i=0 ; i < arg_int ; i++)
		_delay_us(10);
		break;
		case U8X8_MSG_DELAY_MILLI:      // delay arg_int * 1 milli second
		for(int i=0 ; i < arg_int ; i++)
		_delay_ms(1);
		break;
		default:
		return 0;
	}
	return 1;
}

uint8_t ST7565Lcd::gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr){
		switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8
		/*DISPLAY_CLK_DIR |= 1<<DISPLAY_CLK_PIN;
		DISPLAY_DATA_DIR |= 1<<DISPLAY_DATA_PIN;
		DISPLAY_CS_DIR |= 1<<DISPLAY_CS_PIN;
		DISPLAY_DC_DIR |= 1<<DISPLAY_DC_PIN;
		DISPLAY_RESET_DIR |= 1<<DISPLAY_RESET_PIN;*/
		DISPLAY_CLK_CONFIG();
		DISPLAY_DATA_CONFIG();
		DISPLAY_CS_CONFIG();
		DISPLAY_DS_CONFIG();
		DISPLAY_RESET_CONFIG();
		break;              // can be used to setup pins
		case U8X8_MSG_GPIO_SPI_CLOCK:        // Clock pin: Output level in arg_int
		if(arg_int)
		{
			DISPLAY_CLK_SET();
		}else
			DISPLAY_CLK_RESET();
		break;
		case U8X8_MSG_GPIO_SPI_DATA:        // MOSI pin: Output level in arg_int
		if(arg_int){
		DISPLAY_DATA_SET();
		}else
		DISPLAY_DATA_RESET();
		break;
		case U8X8_MSG_GPIO_CS:        // CS (chip select) pin: Output level in arg_int
		if(arg_int){
		DISPLAY_CS_SET();
		}else
		DISPLAY_CS_RESET();
		break;
		case U8X8_MSG_GPIO_DC:        // DC (data/cmd, A0, register select) pin: Output level in arg_int
		if(arg_int){
		DISPLAY_DS_SET();
		}else
		DISPLAY_DS_RESET();
		break;
		
		case U8X8_MSG_GPIO_RESET:     // Reset pin: Output level in arg_int
		if(arg_int){
		DISPLAY_RESET_SET();
		}else
		DISPLAY_RESET_RESET();
		break;
		default:
		if (avr_delay(u8x8, msg, arg_int, arg_ptr))	// check for any delay msgs
		return 1;
		u8x8_SetGPIOResult(u8x8, 1);      // default return value
		break;
	}
	return 1;
}