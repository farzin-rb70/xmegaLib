#ifndef KEY_OBSEVER_H_
#define KEY_OBSEVER_H_

#include <stdio.h>

class KeyObserver
{
public:
	virtual void onKeyPressed(uint8_t ch) = 0;
	virtual void onKeyRelease(uint8_t ch) = 0;
	virtual void onKeyHold(uint8_t ch) = 0;
};


#endif /* KEY_OBSEVER_H_ */