#include "xmegaUART.h"


#ifdef C0
HardwareSerial Serial1(C0);
#endif

#ifdef C1
HardwareSerial Serial2(C1);
#endif

#ifdef D0
HardwareSerial Serial3(D0);
#endif

#ifdef D1
HardwareSerial Serial4(D1);
#endif

#ifdef E0
HardwareSerial Serial5(E0);
#endif

#ifdef E1
HardwareSerial Serial6(E1);
#endif

#ifdef F0
HardwareSerial Serial7(F0);
#endif

#ifdef F1
HardwareSerial Serial8(F1);
#endif






void HardwareSerial::begin(const uint32_t baud, uint8_t config)
{
	// config the rx interrupt
	unsigned char n = (PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) |
	PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	CCP = CCP_IOREG_gc;
	PMIC.CTRL = n;

	// Set the default priority for round-robin scheduling
	PMIC.INTPRI = 0x00;
	
	#ifdef C0
	if(this->_regs==C0){
		PORTC.OUTSET = PIN3_bm;
		PORTC.DIRSET = PIN3_bm;
	}
	#endif

	#ifdef C1
	if(this->_regs==C1){
		PORTC.OUTSET = PIN7_bm;
		PORTC.DIRSET = PIN7_bm;
	}
	#endif

	#ifdef D0
	if(this->_regs==D0){
		PORTD.OUTSET = PIN3_bm;
		PORTD.DIRSET = PIN3_bm;
	}
	#endif

	#ifdef D1
	if(this->_regs==D1){
		PORTD.OUTSET = PIN7_bm;
		PORTD.DIRSET = PIN7_bm;
	}
	#endif

	#ifdef E0
	if(this->_regs==E0){
		PORTE.OUTSET = PIN3_bm;
		PORTE.DIRSET = PIN3_bm;
	}
	#endif

	#ifdef E1
	if(this->_regs==E1){
		PORTE.OUTSET = PIN7_bm;
		PORTE.DIRSET = PIN7_bm;
	}
	#endif

	#ifdef F0
	if(this->_regs==F0){
		PORTF.OUTSET = PIN3_bm;
		PORTF.DIRSET = PIN3_bm;
	}
	#endif

	#ifdef F1
	if(this->_regs==F1){
		PORTF.OUTSET = PIN7_bm;
		PORTF.DIRSET = PIN7_bm;
	}
	#endif

	// uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
	// Asynchronous USART , Data bits: 8 , Stop bits: 1 , Parity: Disabled
	this->_regs->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

	// Receive complete interrupt: High Level
	// Transmit complete interrupt: Disabled
	// Data register empty interrupt: Disabled
	this->_regs->CTRLA = (this->_regs->CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) | USART_RXCINTLVL_HI_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

	// Required Baud rate: 115200
	this->_regs->BAUDCTRLA = 0x2E;
	this->_regs->BAUDCTRLB = ((0x09 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x08;

	// Receiver: On
	// Transmitter: On
	// Double transmission speed mode: Off
	// Multi-processor communication mode: Off
	this->_regs->CTRLB = (this->_regs->CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) | USART_RXEN_bm | USART_TXEN_bm;

	_written = false;
	sei();
}

size_t HardwareSerial::write(uint8_t c)
{
	while ((this->_regs->STATUS & USART_DREIF_bm) == 0)
	;
	this->_regs->DATA = c;
	return 1;
}

uint8_t HardwareSerial::write(uint8_t *str, uint16_t len)
{

	for (uint16_t i = 0; i < len; i++)
	{
		this->write(str[i]);
	}
	return 1;
}

int HardwareSerial::available(void)
{
	return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + this->_rx_buffer_head - this->_rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}
int HardwareSerial::peek(void)
{
	if (_rx_buffer_head == _rx_buffer_tail)
	{
		return -1;
	}
	else
	{
		return _rx_buffer[_rx_buffer_tail];
	}
}
int HardwareSerial::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer_head == _rx_buffer_tail)
	{
		return -1;
	}
	else
	{
		unsigned char c = _rx_buffer[_rx_buffer_tail];
		_rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
		return c;
	}
}

void HardwareSerial::_rx_complete_irq(void)
{
	cli();
	if ((this->_regs->STATUS & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0)
	{
		// No Parity error, read byte and store it in the buffer if there is
		// room
		unsigned char c = this->_regs->DATA;
		rx_buffer_index_t i = (unsigned int)(this->_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != this->_rx_buffer_tail)
		{
			this->_rx_buffer[this->_rx_buffer_head] = c;
			this->_rx_buffer_head = i;
		}
	}
	else
	{
		// Parity error, read byte but discard it
		this->_regs->DATA;
	};

	sei();
}

#ifdef C0
ISR(USARTC0_RXC_vect)
{
	Serial1._rx_complete_irq();
}
#endif

#ifdef C1
ISR(USARTC1_RXC_vect)
{
	Serial2._rx_complete_irq();
}
#endif

#ifdef D0
ISR(USARTD0_RXC_vect)
{
	Serial3._rx_complete_irq();
}
#endif

#ifdef D1
ISR(USARTD1_RXC_vect)
{
	Serial4._rx_complete_irq();
}
#endif

#ifdef E0
ISR(USARTE0_RXC_vect)
{
	Serial5._rx_complete_irq();
}
#endif

#ifdef E1
ISR(USARTE1_RXC_vect)
{
	Serial6._rx_complete_irq();
}
#endif

#ifdef F0
ISR(USARTF0_RXC_vect)
{
	Serial7._rx_complete_irq();
}
#endif

#ifdef F1
ISR(USARTF1_RXC_vect)
{
	Serial8._rx_complete_irq();
}
#endif




