#ifndef _IO_CLASS_H_
#define _IO_CLASS_H_

#include "Arduino.h"
#include "ioInterface.h"

class IOClass : public IOInterface
{
	private:
	uint8_t pin;
	bool activeLevel;
	bool state;
	public:
	IOClass(uint8_t pin, uint8_t dir, bool activeLevel = HIGH)
	{
		this->pin = pin;
		this->activeLevel = activeLevel;
		pinMode(pin, dir);
		this->off();
	};
	~IOClass(){};
	
	inline bool readstate(void) override
	{
		return (bool)digitalRead(this->pin);
	};
	inline void on(void)
	{
		if (!this->activeLevel)
		this->state = LOW;
		else
		this->state = HIGH;
		digitalWrite(this->pin, this->state);
	};
	inline void off(void) override
	{
		if (!this->activeLevel)
		this->state = HIGH;
		else
		this->state = LOW;
		digitalWrite(this->pin, this->state);
	}
	inline void toggle(void) override
	{
		if (this->readstate())
		this->state = LOW;
		else
		this->state = HIGH;
		digitalWrite(this->pin, this->state);
	}
};

#endif