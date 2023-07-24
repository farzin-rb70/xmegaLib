/*
 * ST7565Lcd.h
 *
 * Created: 7/24/2023 1:38:17 PM
 *  Author: rezaei
 */ 


#ifndef ST7565LCD_H_
#define ST7565LCD_H_

#include <stdint.h>
#include "u8g2Lib.h"
#include "font_farsi.h"


class ST7565Lcd : public U8G2Lcd
{
private:
	static uint8_t gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr);
public:
	ST7565Lcd(const u8g2_cb_t *rotation):U8G2Lcd(){
		u8g2_Setup_st7565_ea_dogm132_f(&u8g2, rotation, u8x8_byte_4wire_sw_spi, ST7565Lcd::gpio_and_delay);
	}
	~ST7565Lcd(){}
};


#endif /* ST7565LCD_H_ */