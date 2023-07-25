#include "AT24CXXX.h"


AT24CXXX::AT24CXXX(uint8_t address){
	_address = address;
}

void AT24CXXX::init(){
//	Wire.begin();
}

void AT24CXXX::write(uint16_t address, uint8_t* data, uint8_t length){
// 	Wire.beginTransmission(_address);
// 	Wire.write((int)(address >> 8));
// 	Wire.write((int)(address & 0xFF));
// 	
// 	for(byte i = 0; i < length; i++){
// 		Wire.write(data[i]);
// 	}
// 	
// 	Wire.endTransmission();
// 	delay(EEPROM_DELAY);
}

void AT24CXXX::read(uint16_t address, uint8_t length, uint8_t *buffer){
//     while (TWI0.MASTER.STATUS & TWI_MASTER_BUSSTATE_gm);
// 
//     // Set the device address and write mode
//     TWI0.MASTER.ADDR = (_address << 1) | TWI_MASTER_WRITE;
// 
//     // Wait for the address to be transmitted
//     while (!(TWI0.MASTER.STATUS & TWI_MASTER_WIF_bm));
// 
//     // Check if the device acknowledged the address
//     if ((TWI0.MASTER.STATUS & TWI_MASTER_RXACK_bm)) {
// 	    // Device did not acknowledge the address, handle error here if needed
// 	    // For example: put an error handling code or return from the function with an error code.
//     }
// 
//     // Send the register address to read from
//     TWI0.MASTER.DATA = reg_address;
// 
//     // Wait for the address to be transmitted
//     while (!(TWI0.MASTER.STATUS & TWI_MASTER_WIF_bm));
// 
//     // Check if the device acknowledged the register address
//     if ((TWI0.MASTER.STATUS & TWI_MASTER_RXACK_bm)) {
// 	    // Device did not acknowledge the register address, handle error here if needed
//     }
// 
//     // Send a repeated start condition for read mode
//     TWI0.MASTER.ADDR = (device_address << 1) | TWI_MASTER_READ;
// 
//     // Wait for the address to be transmitted
//     while (!(TWI0.MASTER.STATUS & TWI_MASTER_WIF_bm));
// 
//     // Check if the device acknowledged the read request
//     if ((TWI0.MASTER.STATUS & TWI_MASTER_RXACK_bm)) {
// 	    // Device did not acknowledge the read request, handle error here if needed
//     }
// 
//     // Read multiple bytes
//     for (uint8_t i = 0; i < num_bytes; i++) {
// 	    if (i == (num_bytes - 1)) {
// 		    // For the last byte, send a NACK to the device
// 		    TWI0.MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
// 		    } else {
// 		    // For all other bytes, send an ACK to the device
// 		    TWI0.MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc | TWI_MASTER_ACKACT_bm;
// 	    }
// 
// 	    // Wait for data reception to complete
// 	    while (!(TWI0.MASTER.STATUS & TWI_MASTER_RIF_bm));
// 
// 	    // Read the received data
// 	    data[i] = TWI0.MASTER.DATA;
//     }
// 
//     // Send a stop condition to end the transmission
//     TWI0.MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
}
