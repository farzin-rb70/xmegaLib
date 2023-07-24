/*
 * T6963Lcd.h
 *
 * Created: 7/24/2023 1:40:40 PM
 *  Author: rezaei
 */ 


#ifndef T6963LCD_H_
#define T6963LCD_H_

#include "Arduino.h"
#include <stdint.h>
#include "u8g2Lib.h"
#include "font_farsi.h"




class T6963Lcd : public U8G2Lcd
{
protected:
	static uint8_t gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
public:
	T6963Lcd(const u8g2_cb_t *rotation,uint16_t lcdWidth, uint16_t lcdHight):U8G2Lcd()
	{
		u8g2_Setup_t6963_240x64_f(&u8g2, rotation, u8x8_byte_8bit_8080mode, T6963Lcd::gpio_and_delay);
	};
	~T6963Lcd(){};
};



#endif /* T6963LCD_H_ */