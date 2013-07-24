// Cylon 8 LEDs

#include <io.h>
#include <signal.h>

#define	 LED1		 BIT0
#define	 LED2		 BIT1
#define	 LED3		 BIT2
#define	 LED4		 BIT3
#define	 LED5		 BIT4
#define	 LED6		 BIT5
#define	 LED7		 BIT6
#define	 LED8		 BIT7

int light1 = 1;
int light2 = 0;
int light3 = 0;
int light4 = 0;
int light5 = 0;
int light6 = 0;
int light7 = 0;
int light8 = 0;
unsigned int ms = 800;//20000;
int pass1 = 1;

interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) { // Timer0 ISR
	if (light1) {
		P1DIR = LED1;
		P1OUT = LED1;
		light1 = 0;
		light2 = 1;
	}
	else if (light2) {
		P1DIR = LED2;
		P1OUT = LED2;
		light2 = 0;
		if (pass1) {
			light3 = 1;
		}
		else {
			light1 = 1;
			pass1 = 1;
		}
	}
	else if (light3) {
		P1DIR = LED3;
		P1OUT = LED3;
		light3 = 0;
		if (pass1) {
			light4 = 1;
		}
		else {
			light2 = 1;
		}
	}
	else if (light4) {
		P1DIR = LED4;
		P1OUT = LED4;
		light4 = 0;
		if (pass1) {
			light5 = 1;
		}
		else {
			light3 = 1;
		}
	}
	else if (light5) {
		P1DIR = LED5;
		P1OUT = LED5;
		light5 = 0;
		if (pass1) {
			light6 = 1;
		}
		else {
			light4 = 1;
		}
	}
	else if (light6) {
		P1DIR = LED6;
		P1OUT = LED6;
		light6 = 0;
		if (pass1) {
			light7 = 1;
		}
		else {
			light5 = 1;
		}
	}
	else if (light7) {
		P1DIR = LED7;
		P1OUT = LED7;
		light7 = 0;
		if (pass1) {
			light8 = 1;
		}
		else {
			light6 = 1;
		}
	}
	else if (light8) {
		P1DIR = LED8;
		P1OUT = LED8;
		pass1 = 0;
		light8 = 0;
		light7 = 1;
	}
}

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer
    BCSCTL3 |= LFXT1S_2; // Set ACLK to use internal VLO (12kHz)
    TACTL = TASSEL_1 | MC_1; // TimerA aux clock in UP mode
    TACCTL0 = CCIE; // Enable interrupt for TACCR0 match
    TACCR0 = ms;
    eint(); // Enable interrupts
	_BIS_SR_IRQ(4); // enter low power mode 4
}
