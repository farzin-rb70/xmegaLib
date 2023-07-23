#include "MatrixKeypad.h"


uint8_t rows[ROW_SIZE] = {PA0,PA1,PA2,PA3,PA4};
uint8_t cols[COL_SIZE] = {PA5,PA6,PA7};

char hexaKeys[ROW_SIZE][COL_SIZE] =
{{'*', '#', 'y'},
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'r', '0', 'g'}};

MatrixKeypad matrixKeypad(TIM1,(char*)hexaKeys,rows,cols,5,3);
volatile uint8_t MatrixKeypad::bitMap[MAPSIZE] = {};

MatrixKeypad::MatrixKeypad(uint8_t timerNumber,char *userKeymap, uint8_t *rows , uint8_t *cols ,uint8_t rowCount , uint8_t colCount){
	this->timerNumber = timerNumber;
	this->keymap = userKeymap;
	this->rowPins = rows;
	this->columnPins = cols;
	this->sizeKpd.rows = rowCount;
	this->sizeKpd.columns = colCount;
	for (uint8_t r = 0; r < sizeKpd.rows; r++)
	{
		pinMode(rowPins[r], INPUT_PULLUP);
	}
	for (uint8_t c = 0; c < sizeKpd.columns; c++)
	{
		pinMode(columnPins[c], OUTPUT);
		digitalWrite(columnPins[c],HIGH);
	}
	initTimer10Ms(this->timerNumber);
	this->debounceTime = 500;
	this->holdTime = 3000;
}

MatrixKeypad::~MatrixKeypad(){
	
}

volatile static uint8_t r = 0;
volatile static uint8_t c = 0;

void MatrixKeypad::scan(void){
	digitalWrite(this->columnPins[c], LOW);
	bitMap[r] = 0x00;
	bitWrite(this->bitMap[r], c, !digitalRead(this->rowPins[r]));
	
	if(this->bitMap[r])
	{
		int pressedKeyCode  = r * this->sizeKpd.columns + c;
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
		r++;
		if(r >= this->sizeKpd.rows)
		{
			r = 0;
			digitalWrite(this->columnPins[c], HIGH);
			c++;
			if(c >= this->sizeKpd.columns)
			{
				c=0;
			}
		}
	}
}

