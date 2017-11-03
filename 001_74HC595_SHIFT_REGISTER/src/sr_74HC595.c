/*
 * 74HC595 Shift Register example
 * Copyright (C) 2017 Szymon Szantula
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#include "sr_74HC595.h"

volatile uint8_t data = 0x00;

volatile uint8_t bit_count = 0x00;

static void InterrupHandlerB()
{
	SHIFTREG_PORT |= _BV(SCK);
	bit_count++;
}

static void InterrupHandlerA()
{
	if(bit_count < 8)
	{
		SHIFTREG_PORT &= ~_BV(SCK);
		if((data>>bit_count)&1)
			SHIFTREG_PORT |= _BV(SI);
		else
			SHIFTREG_PORT &= ~_BV(SI);
	}
	else
	{
		SHIFTREG_PORT &= ~_BV(SCK);
		TCCR0B = 0x00;
		TIMSK0 = 0x00;
		TIFR0 = 0x00;
		TCNT0 = 0x00;
		SHIFTREG_PORT |= _BV(RCK);
	}
}

void ShiftDataIn(uint8_t input_data)
{
	data = input_data;
	bit_count = 0;
	SHIFTREG_PORT &= ~_BV(RCK);

	SHIFTREG_PORT = (SHIFTREG_PORT & ~_BV(SI)) | (( 1 & data)<<SI);
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		TCCR0B |= _BV(CS01);
		TIMSK0 |= _BV(OCIE0B) | _BV(OCIE0A);
	}
}

ISR(TIMER0_COMPA_vect)
{
	InterrupHandlerA();
}


ISR(TIMER0_COMPB_vect)
{
	InterrupHandlerB();
}

void InitShiftRegister()
{
	/* setting up outputs */
	SHIFTREG_DDR |= _BV(RCK) | _BV(SI) | _BV(G) | _BV(SCLR) | _BV(SCK);
	SHIFTREG_PORT &= ~_BV(RCK) & ~_BV(SCK);
	ClearRegister();
	DisableOutput();

	/* setting up timer0 */
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		TCCR0A = 0x00; // clear tim0 control register a
		TCCR0B = 0x00; // clear tim0 control register b
		TCNT0 = 0x00; // clear tim0 counter register
		OCR0A = 0x1f; // set compare register a
		OCR0B = 0x0f; // set compare register b
		TIMSK0 = 0x00; // clear interrupt maskt register
		TCCR0A |= 1<<WGM01; // setup CTC mode
	}

	/* preparing global variables */
	data = 0x00;
	bit_count = 0x00;
}

void EnableOutput()
{
	SHIFTREG_PORT &= ~_BV(G);
}

void DisableOutput()
{
	SHIFTREG_PORT |= _BV(G);
}

void ClearRegister()
{
	SHIFTREG_PORT &= ~_BV(SCLR);
	_delay_us(100);
	SHIFTREG_PORT |= _BV(SCLR);
}


