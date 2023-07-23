#ifndef XMEGAUART_H_
#define XMEGAUART_H_

#include "avr/interrupt.h"
#include "Print.h"

//#define SERIAL1En
//#define SERIAL2En 
#define SERIAL3En 
//#define SERIAL4En 
#define SERIAL5En 
//#define SERIAL6En 
//#define SERIAL7En 
//#define SERIAL8En 

#if defined(_ATXMEGA128A_1U_)  || defined(_ATXMEGA128A_4U_)

#if  defined(USARTC0) && defined(SERIAL1En)
#define C0 ((USART_t *)&USARTC0)
#endif

#if defined(USARTC1) && defined(SERIAL2En)
#define C1 ((USART_t *)&USARTC1)
#endif

#if defined(USARTD0) && defined(SERIAL3En)
#define D0 ((USART_t *)&USARTD0)
#endif

#if defined(USARTD1) && defined(SERIAL4En)
#define D1 ((USART_t *)&USARTD1)
#endif

#if defined(USARTE0) && defined(SERIAL5En)
#define E0 ((USART_t *)&USARTE0)
#endif

#endif


#if defined(_ATXMEGA128A_1U_) 

#if defined(USARTE1) && defined(SERIAL6En)
#define E1 ((USART_t *)&USARTE1)
#endif

#if defined(USARTF0) && defined(SERIAL7En)
#define F0 ((USART_t *)&USARTF0)
#endif

#if defined(USARTF1) && defined(SERIAL8En)
#define F1 ((USART_t *)&USARTF1)
#endif

#endif




#define SERIAL_RX_BUFFER_SIZE 1024

#if !defined(SERIAL_TX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_TX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE > 256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if (SERIAL_RX_BUFFER_SIZE > 256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Print
{
protected:
	bool _written;
	volatile rx_buffer_index_t _rx_buffer_head;
	volatile rx_buffer_index_t _rx_buffer_tail;
	unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];

public:
	USART_t *_regs;
	HardwareSerial(USART_t *serial) : _regs(serial)
	{
		this->begin(115200);
	}
	~HardwareSerial()
	{
	}
	void begin(const uint32_t baud) { begin(baud, SERIAL_8N1); }
	void begin(const uint32_t baud, uint8_t config);
	int available(void);
	int peek(void);
	int read(void);
	virtual size_t write(uint8_t);
	uint8_t write(uint8_t *str, uint16_t len);
	inline uint8_t write(const char *str)
	{
		return write((uint8_t *)str, strlen(str));
	}
	inline uint8_t write(String str) { return write((uint8_t *)str.c_str(), (unsigned int)str.length()); }
	void _rx_complete_irq(void);
};

#ifdef C0
extern HardwareSerial Serial1;
#endif

#ifdef C1
extern HardwareSerial Serial2;
#endif

#ifdef D0
extern HardwareSerial Serial3;
#endif

#ifdef D1
extern HardwareSerial Serial4;
#endif

#ifdef E0
extern HardwareSerial Serial5;
#endif

#ifdef E1
extern HardwareSerial Serial6;
#endif

#ifdef F0
extern HardwareSerial Serial7;
#endif

#ifdef F1
extern HardwareSerial Serial8;
#endif

#endif /* XMEGAUART_H_ */