#ifndef STREAM_H_
#define STREAM_H_

#include "WString.h"

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2

class Stream
{
public:
	virtual size_t print(const String &) = 0;
	virtual size_t print(const char[]) = 0;
	virtual size_t print(char) = 0;
	virtual size_t print(unsigned char, int = DEC) = 0;
	virtual size_t print(int, int = DEC) = 0;
	virtual size_t print(unsigned int, int = DEC) = 0;
	virtual size_t print(long, int = DEC) = 0;
	virtual size_t print(unsigned long, int = DEC) = 0;
	virtual size_t print(double, int = 2) = 0;

	virtual size_t println(const __FlashStringHelper *) = 0;
	virtual size_t println(const String &s) = 0;
	virtual size_t println(const char[]) = 0;
	virtual size_t println(char) = 0;
	virtual size_t println(unsigned char, int = DEC) = 0;
	virtual size_t println(int, int = DEC) = 0;
	virtual size_t println(unsigned int, int = DEC) = 0;
	virtual size_t println(long, int = DEC) = 0;
	virtual size_t println(unsigned long, int = DEC) = 0;
	virtual size_t println(double, int = 2) = 0;
	virtual size_t println(void) = 0;

	virtual int16_t printf(const char *format, ...) = 0;
	virtual int16_t printf(const __FlashStringHelper *format, ...) = 0;
private:
};



#endif /* STREAM_H_ */