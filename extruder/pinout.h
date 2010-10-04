
#ifndef	_PINOUT_H
#define	_PINOUT_H

#include	"arduino.h"

//RS485 Interface pins
#define RX_ENABLE_PIN DIO4
#define TX_ENABLE_PIN DIO16

// Control pins for the A3949 chips
#define H1D DIO7
#define H1E DIO5
#define H2D DIO8
#define H2E DIO6

// PWM versions of the enable_pins
#define H1E_PWM OCR0B
#define H2E_PWM OCR0A

//Step/Dir Pins from motherboard to extruder 
//IMPORTANT: Assumes that the step pin is on PCIE0
#define E_STEP_PIN DIO10
#define E_DIR_PIN DIO9

//Trimpot is on AIO0, pin 23
#define TRIM_POT AIO0
#define TRIM_POT_CHANNEL 0

//Debug LED will blink on RS485 transmission
#define DEBUG_LED DIO13

//Read analog voltage from thermistor
#define TEMP_PIN AIO3
#define TEMP_PIN_CHANNEL 3

// list of PWM-able pins and corresponding timers
// timer1 is used for step timing so don't use OC1A/OC1B (DIO9/DIO10)
// OC0A												DIO6
// OC0B												DIO5
// OC1A												DIO9
// OC1B												DIO10
// OC2A												DIO11
// OC2B												DIO3

#define	HEATER_PIN						DIO11
#define	HEATER_PWM						OCR2A

#define BED_PIN							DIO12						

#define ANALOG_MASK	(MASK(TRIM_POT_CHANNEL) | MASK(TEMP_PIN_CHANNEL))

/*
	Intercom
*/
#define enable_transmit()			do { WRITE(TX_ENABLE_PIN,1);  WRITE(RX_ENABLE_PIN,0); } while(0)
#define disable_transmit()			do { WRITE(TX_ENABLE_PIN,0);  WRITE(RX_ENABLE_PIN,0); } while(0)

/*
	Motors
*/

#define enable_motors()				do { TCCR0A |= MASK(COM0A1) | MASK(COM0B1); } while (0)
#define disable_motors()			do { TCCR0A &= ~MASK(COM0A1) & ~MASK(COM0B1); } while (0)

/*
	Heater
*/

#ifdef	HEATER_PWM
	#define	enable_heater()			do { TCCR2A |=  MASK(COM2A1); } while (0)
	#define	disable_heater()		do { TCCR2A &= ~MASK(COM2A1); } while (0)
#else
	#define	enable_heater()			WRITE(HEATER_PIN, 1)
	#define	disable_heater()		WRITE(HEATER_PIN, 0)
#endif


#endif	/* _PINOUT_H */
