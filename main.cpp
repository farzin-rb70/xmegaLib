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
#include "u8g2Lib.h"
#include "ST7565Lcd.h"
#include "PersianReshaper.h"
#include "eeprom.h"



InputDevice *pKeypad;
Stream *pDebugPort;
IOInterface *pBuzzer;
Eeprom *externalEEprom;

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
ST7565Lcd pos4lcd(U8G2_R0);
U8G2Lcd *pLcd;

int main(void)
{
	pKeypad = &matrixKeypad;
	//posKeypad = &iKeys;
	pDebugPort=&Serial5;
	pBuzzer =&buzzer;
	pLcd = &pos4lcd;
	
	
	clockConfig();
	millisTimerConfig();
	pKeypad->registerOb(&posLogic);
	
	
	pLcd->begin(122,32);
	pLcd->setFlipMode(1);
	pLcd->setContrast(20);
	pLcd->setFontMode(1);
	pLcd->enableUTF8Print();
	pLcd->setFontDirection(0);
	
	pLcd->setFontRefHeightExtendedText();
	pLcd->setFont(IRANSansXMedium1);
	pLcd->setDrawColor(2);
	pLcd->clearBuffer();
	int8_t textDescent = pLcd->getDescent();
	int8_t textAscent = pLcd->getAscent();
	int8_t verticalFreeSpace = 16 -  textAscent - textDescent;
	verticalFreeSpace = verticalFreeSpace >= 0 ? verticalFreeSpace : 0;
	u8g2_uint_t yCursor =16 + textDescent -	(verticalFreeSpace / 2);
	pLcd->setCursor(0,yCursor);
	pLcd->print("English test");
	
	yCursor = 32 + textDescent - (verticalFreeSpace / 2);
	pLcd->setCursor(10,yCursor);
	char* testText = "تست فارسی نویسی";
	pLcd->print(prReshaper(testText));
	pLcd->updateDisplay();
	
	
	while (1)
	{
	}
}