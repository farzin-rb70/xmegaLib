#include "xmegaBasicTimer.h"


TC0_t *tc_regs[] = {
	(TC0_t *)&TCC0,
	(TC0_t *)&TCC1,
	(TC0_t *)&TCD0,
	(TC0_t *)&TCD1,
	(TC0_t *)&TCE0
	};


void tc_disable(TC0_t *ptc)
{
	// Timer/Counter off
	ptc->CTRLA = TC_CLKSEL_OFF_gc;
	// Issue a reset command
	ptc->CTRLFSET = TC_CMD_RESET_gc;
}

void initTimer10Ms(uint8_t timerNumber){
	unsigned char s;

	// Note: The correct PORTC direction for the Compare Channels
	// outputs is configured in the ports_init function.

	// Save interrupts enabled/disabled state
	s=SREG;
	// Disable interrupts
	cli();

	// Disable and reset the timer/counter just to be sure
	tc_disable(tc_regs[timerNumber]);
	// Clock source: ClkPer/1
	tc_regs[timerNumber]->CTRLA=TC_CLKSEL_DIV1_gc;
	// Mode: Normal Operation, Overflow Int./Event on TOP
	// Compare/Capture on channel A: Off
	// Compare/Capture on channel B: Off
	tc_regs[timerNumber]->CTRLB=(0<<TC1_CCBEN_bp) | (0<<TC1_CCAEN_bp) |
	TC_WGMODE_NORMAL_gc;
	// Capture event source: None
	// Capture event action: None
	tc_regs[timerNumber]->CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

	// Set Timer/Counter in Normal mode
	tc_regs[timerNumber]->CTRLE=TC_BYTEM_NORMAL_gc;

	// Overflow interrupt: High Level
	// Error interrupt: Disabled
	tc_regs[timerNumber]->INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_HI_gc;

	// Compare/Capture channel A interrupt: Disabled
	// Compare/Capture channel B interrupt: Disabled
	tc_regs[timerNumber]->INTCTRLB=TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

	// High resolution extension: Off
	tc_regs[timerNumber]->CTRLA&= ~HIRES_HREN1_bm;

	// Clear the interrupt flags
	tc_regs[timerNumber]->INTFLAGS=TCC1.INTFLAGS;
	// Set Counter register
	tc_regs[timerNumber]->CNT=0x0000;
	// Set Period register
	tc_regs[timerNumber]->PER=0x4E1F;
	// Set channel A Compare/Capture register
	tc_regs[timerNumber]->CCA=0x0000;
	// Set channel B Compare/Capture register
	tc_regs[timerNumber]->CCB=0x0000;

	// Restore interrupts enabled/disabled state
	SREG=s;
	sei();
}






volatile unsigned long millisTimer = 0;


void clockConfig(void){
	unsigned char n,s;
	// Save interrupts enabled/disabled state
	s=SREG;
	// Disable interrupts
	cli();

	// Internal 32 kHz RC oscillator initialization
	// Enable the internal 32 kHz RC oscillator
	OSC.CTRL|=OSC_RC32KEN_bm;
	// Wait for the internal 32 kHz RC oscillator to stabilize
	while ((OSC.STATUS & OSC_RC32KRDY_bm)==0);

	// Internal 32 MHz RC oscillator initialization
	// Enable the internal 32 MHz RC oscillator
	OSC.CTRL|=OSC_RC32MEN_bm;

	// System Clock prescaler A division factor: 1
	// System Clock prescalers B & C division factors: B:1, C:1
	// ClkPer4: 32000.000 kHz
	// ClkPer2: 32000.000 kHz
	// ClkPer:  32000.000 kHz
	// ClkCPU:  32000.000 kHz
	n=(CLK.PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm | CLK_PSBCDIV0_bm))) |
	CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
	CCP=CCP_IOREG_gc;
	CLK.PSCTRL=n;

	// Internal 32 MHz RC osc. calibration reference clock source: 32.768 kHz Internal Osc.
	OSC.DFLLCTRL=(OSC.DFLLCTRL & (~(OSC_RC32MCREF_gm | OSC_RC2MCREF_bm))) | OSC_RC32MCREF_RC32K_gc;
	// Enable the auto-calibration of the internal 32 MHz RC oscillator
	DFLLRC32M.CTRL|=DFLL_ENABLE_bm;

	// Wait for the internal 32 MHz RC oscillator to stabilize
	while ((OSC.STATUS & OSC_RC32MRDY_bm)==0);

	// Select the system clock source: 32 MHz Internal RC Osc.
	n=(CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC32M_gc;
	CCP=CCP_IOREG_gc;
	CLK.CTRL=n;

	// Disable the unused oscillators: 2 MHz, external clock/crystal oscillator, PLL
	OSC.CTRL&= ~(OSC_RC2MEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm);

	// ClkPer output disabled
	PORTCFG.CLKEVOUT&= ~(PORTCFG_CLKOUTSEL_gm | PORTCFG_CLKOUT_gm);
	// Restore interrupts enabled/disabled state
	SREG=s;
	// Restore optimization for size if needed
}



void millisTimerConfig(void)
{
	unsigned char s;
	unsigned char n;

	// Note: The correct PORTC direction for the Compare Channels
	// outputs is configured in the ports_init function.

	// Save interrupts enabled/disabled state
	s=SREG;
	// Disable interrupts
	cli();

	// Disable and reset the timer/counter just to be sure
	tc_disable(&TCC0);
	// Clock source: ClkPer/1
	TCC0.CTRLA=TC_CLKSEL_DIV1_gc;
	// Mode: Normal Operation, Overflow Int./Event on TOP
	// Compare/Capture on channel A: Off
	// Compare/Capture on channel B: Off
	// Compare/Capture on channel C: Off
	// Compare/Capture on channel D: Off
	TCC0.CTRLB=(0<<TC0_CCDEN_bp) | (0<<TC0_CCCEN_bp) | (0<<TC0_CCBEN_bp) | (0<<TC0_CCAEN_bp) |
	TC_WGMODE_NORMAL_gc;
	// Capture event source: None
	// Capture event action: None
	TCC0.CTRLD=TC_EVACT_OFF_gc | TC_EVSEL_OFF_gc;

	// Set Timer/Counter in Normal mode
	TCC0.CTRLE=TC_BYTEM_NORMAL_gc;

	// Overflow interrupt: High Level
	// Error interrupt: Disabled
	TCC0.INTCTRLA=TC_ERRINTLVL_OFF_gc | TC_OVFINTLVL_HI_gc;

	// Compare/Capture channel A interrupt: Disabled
	// Compare/Capture channel B interrupt: Disabled
	// Compare/Capture channel C interrupt: Disabled
	// Compare/Capture channel D interrupt: Disabled
	TCC0.INTCTRLB=TC_CCDINTLVL_OFF_gc | TC_CCCINTLVL_OFF_gc | TC_CCBINTLVL_OFF_gc | TC_CCAINTLVL_OFF_gc;

	// High resolution extension: Off
	HIRESC.CTRLA&= ~HIRES_HREN0_bm;

	// Advanced Waveform Extension initialization
	// Disable locking the AWEX configuration registers just to be sure
	n=MCU.AWEXLOCK & (~MCU_AWEXCLOCK_bm);
	CCP=CCP_IOREG_gc;
	MCU.AWEXLOCK=n;
	// Restore optimization for size if needed

	// Pattern generation: Off
	// Dead time insertion: Off
	AWEXC.CTRL=(0<<AWEX_PGM_bp) | (0<<AWEX_CWCM_bp) | (0<<AWEX_DTICCDEN_bp) | (0<<AWEX_DTICCCEN_bp) |
	(0<<AWEX_DTICCBEN_bp) | (0<<AWEX_DTICCAEN_bp);

	// Fault protection initialization
	// Fault detection on OCD Break detection: On
	// Fault detection restart mode: Latched Mode
	// Fault detection action: None (Fault protection disabled)
	AWEXC.FDCTRL=(AWEXC.FDCTRL & (~(AWEX_FDDBD_bm | AWEX_FDMODE_bm | AWEX_FDACT_gm))) |
	(0<<AWEX_FDDBD_bp) | (0<<AWEX_FDMODE_bp) | AWEX_FDACT_NONE_gc;
	// Fault detect events:
	// Event channel 0: Off
	// Event channel 1: Off
	// Event channel 2: Off
	// Event channel 3: Off
	// Event channel 4: Off
	// Event channel 5: Off
	// Event channel 6: Off
	// Event channel 7: Off
	AWEXC.FDEMASK=0b00000000;
	// Make sure the fault detect flag is cleared
	AWEXC.STATUS|=AWEXC.STATUS & AWEX_FDF_bm;

	// Clear the interrupt flags
	TCC0.INTFLAGS=TCC0.INTFLAGS;
	// Set Counter register
	TCC0.CNT=0x0000;
	// Set Period register
	TCC0.PER=0x7CFF;
	// Set channel A Compare/Capture register
	TCC0.CCA=0x0000;
	// Set channel B Compare/Capture register
	TCC0.CCB=0x0000;
	// Set channel C Compare/Capture register
	TCC0.CCC=0x0000;
	// Set channel D Compare/Capture register
	TCC0.CCD=0x0000;

	// Restore interrupts enabled/disabled state
	SREG=s;
}

inline unsigned long millis(void){
	return millisTimer;
}


ISR(TCC0_OVF_vect)
{
	// Save interrupts enabled/disabled state
	unsigned char s = SREG;
	// Disable interrupts
	cli();
	millisTimer++;
	// Restore interrupts enabled/disabled state
	TCC0.INTFLAGS=TCC0.INTFLAGS;
	SREG = s;
}