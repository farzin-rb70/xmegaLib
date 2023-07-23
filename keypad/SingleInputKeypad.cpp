#include "SingleInputKeypad.h"


#define KEPAD_SIZE 19


uint8_t pinsList[KEPAD_SIZE] =
{/*PE0,PE5,PE2,
PD6,PE4,PE3,
PD7,PE1,PB4,
PB2,PB3,PB6,
PB1,PB0,PB5,
PF3,PF2,PE6,PE7*/};

char iKeyChar[KEPAD_SIZE] =
{'*', '#','y',
	'1', '2', '3',
	'4', '5', '6',
	'7', '8', '9',
	'r', '0', 'g',
'A', 'B', 'C','D'};

SingleInputKeypad iKeys(TIM1,iKeyChar,pinsList,KEPAD_SIZE);

SingleInputKeypad::SingleInputKeypad(uint8_t timerNumber, char *userKeymap , uint8_t *pinList , uint8_t pinCount)
{
	this->keymap = userKeymap;
	this->pinList = pinList;
	this->pinCount = pinCount;
	for (uint8_t i=0 ; i<pinCount ; i++)
	{
		pinMode(pinList[i],INPUT_PULLUP);
	}
	initTimer10Ms(this->timerNumber);
	this->debounceTime = 500;
	this->holdTime = 3000;
}
SingleInputKeypad::~SingleInputKeypad()
{
	
}
volatile uint8_t pinNumber = 0;
void SingleInputKeypad::scan(void)
{
	
	if(!digitalRead(this->pinList[pinNumber])){
		int pressedKeyCode  = pinNumber;
		if(this->key.kcode == pressedKeyCode)
		{
			if(millis() - (this->startTime) > this->debounceTime)
			{
				if(this->key.kstate == IDLE){
					this->key.kcode = pressedKeyCode;
					this->key.kchar = keymap[pressedKeyCode];
					this->key.kstate = PRESSED;
					cli();
					this->notify();
					sei();
					this->startTime = millis();
				}
			}
			if(millis() - (this->startTime) > this->holdTime)
			{
				if(this->key.kstate == PRESSED){
					this->key.kcode = pressedKeyCode;
					this->key.kchar = keymap[pressedKeyCode];
					this->key.kstate = HOLD;
					cli();
					this->notify();
					sei();
					this->startTime = millis();
				}
			}
		}
		this->key.kcode = pressedKeyCode;
		}
		else
		{
		if(this->key.kstate == PRESSED || this->key.kstate == HOLD){
			this->key.kstate = RELEASED;
			cli();
			this->notify();
			sei();
		}

		this->key.kstate = IDLE;
	}
	if(this->key.kstate == IDLE)
	{
	pinNumber++;
	}
}