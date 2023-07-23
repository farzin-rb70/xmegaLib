/*
* touchKeypad.h
*
* Created: 7/19/2023 3:01:44 PM
*  Author: rezaei
*/


#ifndef MATRIX_KEYPAD_H_
#define MATRIX_KEYPAD_H_

#include "Arduino.h"
#include <stdint.h>
#include "Key.h"
#include "KeyObserver.h"
#include "InputDevice.h"


#define ROW_SIZE 5
#define COL_SIZE 3

#define MAPSIZE ROW_SIZE


typedef struct
{
	uint8_t rows;
	uint8_t columns;
} KeypadSize;

class MatrixKeypad : public InputDevice
{
	private:
	KeyObserver *observer;
	uint8_t timerNumber;
	uint16_t holdTime;
	uint16_t debounceTime;
	Key key;
	unsigned long startTime;
	volatile static uint8_t bitMap[MAPSIZE];
	char *keymap;
	KeypadSize sizeKpd;
	uint8_t *rowPins;
	uint8_t *columnPins;
	
	void notify() override
	{
		if(this->key.kstate == PRESSED){
			observer->onKeyPressed(this->key.kchar);
			}else if(this->key.kstate == RELEASED){
			observer->onKeyRelease(this->key.kchar);
			}else if(this->key.kstate == HOLD){
			observer->onKeyHold(this->key.kchar);
		}
	}
	
	
	public:
	MatrixKeypad(uint8_t timerNumber ,char *userKeymap , uint8_t *rows , uint8_t *cols ,uint8_t rowCount , uint8_t colCount);
	~MatrixKeypad();
	void registerOb(KeyObserver *observer) override
	{
		this->observer = observer;
	}
	void scan(void) override;
};

extern MatrixKeypad matrixKeypad;

#endif /* MATRIX_KEYPAD_H_ */