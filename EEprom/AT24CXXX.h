/*
* IncFile1.h
*
* Created: 7/25/2023 10:27:37 AM
*  Author: rezaei
*/


#ifndef AT24CXXX_H_
#define AT24CXXX_H_

#define EEPROM_DELAY 3

#include <stdint.h>
#include "eeprom.h"
#include "avr/io.h"

class AT24CXXX : public Eeprom
{
public:
	AT24CXXX(uint8_t address);
	void init();
protected:
	void write(uint16_t address, uint8_t* data, uint8_t length) override; //write multiple bytes to EEPROM
	void read(uint16_t address, uint8_t length, uint8_t *buffer) override; //read multiple bytes to EEPROM
private:
	uint8_t _address;
};


#endif /* AT24CXXX_H_ */