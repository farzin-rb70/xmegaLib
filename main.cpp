#include <avr/io.h>
#include <util/delay.h>
#include <fcntl.h>

#include "Arduino.h"
#include "KeyObserver.h"
#include "MatrixKeypad.h"
#include "SingleInputKeypad.h"
#include "Stream.h"
#include "ioInterface.h"
#include "ioClass.h"
#include "xmegaUART.h"



InputDevice *pKeypad;
Stream *pDebugPort;
IOInterface *pBuzzer;

IOClass buzzer(PE1,OUTPUT,LOW);


class logic : public KeyObserver
{
public:
	logic(){}
	~logic(){}
protected:
	void onKeyPressed(uint8_t ch) override {
		pDebugPort->printf("pressed Key : %c\n" , ch);
		if(ch == '2')
		{
			pBuzzer->on();
		}
	}
	void onKeyRelease(uint8_t ch) override {
		pDebugPort->printf("released : %c\n" , ch);
		if(ch == '2')
		{
			pBuzzer->off();
		}
	}
	void onKeyHold(uint8_t ch) override {
		pDebugPort->printf("holdKey : %c\n" , ch);
	}
private:
};


ISR(TCC1_OVF_vect)
{
	pKeypad->scan();
}

logic posLogic;

int main(void)
{
	pKeypad = &matrixKeypad;
	//posKeypad = &iKeys;
	pDebugPort=&Serial5;
	pBuzzer =&buzzer;
	
	
	clockConfig();
	millisTimerConfig();
	pKeypad->registerOb(&posLogic);
	
	while (1)
	{
	}
}