/*
 * SingleInputKeypad.h
 *
 * Created: 7/23/2023 11:00:20 AM
 *  Author: rezaei
 */ 


#ifndef SINGLEINPUTKEYPAD_H_
#define SINGLEINPUTKEYPAD_H_

#include "Arduino.h"
#include <stdint.h>
#include "Key.h"
#include "InputDevice.h"
#include "KeyObserver.h"

class SingleInputKeypad : public InputDevice
{
private:
	KeyObserver *observer;
	char *keymap;
	uint8_t *pinList;
	uint8_t pinCount;
	uint8_t timerNumber;
	uint16_t holdTime;
	uint16_t debounceTime;
	Key key;
	unsigned long startTime;
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
	SingleInputKeypad(uint8_t timerNumber, char *userKeymap , uint8_t *pinList , uint8_t pinCount);
	~SingleInputKeypad();
	void registerOb(KeyObserver *observer) override
	{
		this->observer = observer;
	}
	void scan(void) override;
};

extern SingleInputKeypad iKeys;

#endif /* SINGLEINPUTKEYPAD_H_ */