#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_

#include "KeyObserver.h"

class InputDevice {
	public:
	virtual void registerOb(KeyObserver *observer) = 0;
	virtual void notify() = 0;
	virtual void scan(void) = 0;
};





#endif /* INPUTDEVICE_H_ */