#ifndef IOINTERFACE_H_
#define IOINTERFACE_H_

class IOInterface
{
public:
	virtual bool readstate(void) = 0;
	virtual void on(void) = 0;
	virtual void off(void) = 0;
	virtual void toggle(void) = 0;
};



#endif /* IOINTERFACE_H_ */