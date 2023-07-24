/*
 * T6963Lcd.cpp
 *
 * Created: 7/24/2023 1:40:49 PM
 *  Author: rezaei
 */ 
#include "T6963Lcd.h"
/*
#define LCD_DB0 PK7
#define LCD_DB1 PK6
#define LCD_DB2 PK5
#define LCD_DB3 PK4
#define LCD_DB4 PK3
#define LCD_DB5 PK2
#define LCD_DB6 PK1
#define LCD_DB7 PK0
#define LCD_RST PJ7
#define LCD_CS  PJ6
#define LCD_RS  PJ5
#define LCD_WR  PJ4
#define LCD_RD  PJ3
#define LCD_FS  PQ0


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

uint8_t T6963Lcd::gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8
		pinMode(LCD_DB0,OUTPUT_PULLUP);
		pinMode(LCD_DB1,OUTPUT_PULLUP);
		pinMode(LCD_DB2,OUTPUT_PULLUP);
		pinMode(LCD_DB3,OUTPUT_PULLUP);
		pinMode(LCD_DB4,OUTPUT_PULLUP);
		pinMode(LCD_DB5,OUTPUT_PULLUP);
		pinMode(LCD_DB6,OUTPUT_PULLUP);
		pinMode(LCD_DB7,OUTPUT_PULLUP);
		
		pinMode(LCD_RST,OUTPUT_PULLUP);
		pinMode(LCD_CS,OUTPUT_PULLUP);
		pinMode(LCD_RS,OUTPUT_PULLUP);
		pinMode(LCD_WR,OUTPUT_PULLUP);
		
		pinMode(LCD_RD,OUTPUT_PULLUP);
		pinMode(LCD_FS,OUTPUT_PULLUP);
		
		digitalWrite(LCD_FS,LOW);
		digitalWrite(LCD_RD,HIGH);
		
		case U8X8_MSG_DELAY_I2C:				  // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
		break;							         // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
		case U8X8_MSG_GPIO_D0:				    // D0 or SPI clock pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB0,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB0,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB1,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB1,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB2,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB2,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB3,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB3,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB4,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB4,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB5,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB5,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB6,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB6,LOW);
		}
		break;
		case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_DB7,HIGH);
		}
		else
		{
			digitalWrite(LCD_DB7,LOW);
		}
		break;
		case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_WR,HIGH);
		}
		else
		{
			digitalWrite(LCD_WR,LOW);
		}
		break;
		case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_CS,HIGH);
		}
		else
		{
			digitalWrite(LCD_CS,LOW);
		}
		break;
		case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_RS,HIGH);
		}
		else
		{
			digitalWrite(LCD_RS,LOW);
		}
		break;
		case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
		if(arg_int)
		{
			digitalWrite(LCD_RST,HIGH);
		}
		else
		{
			digitalWrite(LCD_RST,LOW);
		}
		break;
		default:
		if (u8x8_avr_delay(u8x8, msg, arg_int, arg_ptr))	// check for any delay msgs
		return 1;
		u8x8_SetGPIOResult(u8x8, 1);			// default return value
		break;
	}
	return 1;
}
*/