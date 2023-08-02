/*
* eeprom.h
*
* Created: 7/25/2023 9:37:39 AM
*  Author: rezaei
*/


#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

class Eeprom
{
protected:
	virtual void write(uint16_t address, uint8_t* data, uint16_t length) = 0;
	virtual void read(uint16_t address, uint8_t length, uint8_t *buffer) = 0;
public:
	inline uint8_t readByte(uint16_t address)
	{
		uint8_t e = 0;
		this->read(address,sizeof(uint8_t),&e);
		return e;
	}
	inline uint16_t raedInt16(uint16_t address){
		uint16_t e = 0;
		this->read(address,sizeof(uint16_t),(uint8_t*)&e);
		return e;
	}
	inline uint32_t raedInt32(uint16_t address){
		uint32_t e = 0;
		this->read(address,sizeof(uint32_t),(uint8_t*)&e);
		return e;
	}
	inline uint8_t writeByte(uint16_t address , uint8_t value)
	{
		this->write(address,&value,sizeof(uint8_t));
		return value;
	};
	inline uint16_t writeInt16(uint16_t address , uint16_t value)
	{
		this->write(address,(uint8_t *)&value,sizeof(uint16_t));
		return value;
	}
	inline uint32_t writeInt32(uint16_t address , uint32_t value)
	{
		this->write(address,(uint8_t *)&value,sizeof(uint32_t));
		return value;
	}
	
	template< typename T > T &get(uint16_t address, T &value ){
		uint8_t *e = (uint8_t *)value;
		this->read(address,sizeof(T),e);
		return value;
	}
	
	template< typename T > const T &put( uint16_t address, const T &value ){
		uint8_t * e= (uint8_t*)&value;
		this->write(address,e,sizeof(T));
		return value;
	}
};


#endif /* EEPROM_H_ */