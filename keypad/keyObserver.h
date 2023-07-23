#ifndef INPUT_DEVICE_H_
#define INPUT_DEVICE_H_

#include <stdio.h>

class KeyObserver
{
public:
	virtual void onKeyPressed(uint8_t ch) = 0;
	virtual void onKeyRelease(uint8_t ch) = 0;
	virtual void onKeyHold(uint8_t ch) = 0;
};


#endif /* INPUT_DEVICE_H_ */