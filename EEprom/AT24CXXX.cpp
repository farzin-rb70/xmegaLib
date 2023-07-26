#include "AT24CXXX.h"
#include "Wire.h"


AT24CXXX::AT24CXXX(uint8_t address){
	_address = address;
	this->init();
}

void AT24CXXX::init(){
	xmWireC.begin();
	pinMode(PB1,OUTPUT);
	digitalWrite(PB1,LOW);
}

void AT24CXXX::write(uint16_t address, uint8_t* data, uint8_t length){
	xmWireC.beginTransmission(_address);
	xmWireC.write((int)(address >> 8));
	xmWireC.write((int)(address & 0xFF));
	
	for(uint8_t i = 0; i < length; i++){
		xmWireC.write(data[i]);
	}
	
	xmWireC.endTransmission();
	delay(EEPROM_DELAY);
}

void AT24CXXX::read(uint16_t address, uint8_t length, uint8_t *buffer){
	  xmWireC.beginTransmission(_address);
	  xmWireC.write((int)(address >> 8));
	  xmWireC.write((int)(address & 0xFF));
	  xmWireC.endTransmission();
	  xmWireC.requestFrom(_address, length);
	  
	  for(int i = 0; i < length; i++){
		  if(xmWireC.available()){
			  buffer[i] = xmWireC.read();
		  }
	  }
	  delay(EEPROM_DELAY);
}
