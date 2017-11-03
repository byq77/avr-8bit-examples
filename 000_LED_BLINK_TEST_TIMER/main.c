/*
 * Blinky - blinking led diode using timer1
 * Copyright (C) 2017 Szymon Szantula
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

void SetTimer1(void)
{
	TCCR1A = 0; // reseting control register A
	TCCR1B = 0; // reseting control register B
	TCNT1 = 0; // reseting counter register
	OCR1A = 15625; // set compare register
	TCCR1A |= 1<<COM1A0 ; // enable pin state toggle on compare match
	TCCR1B |= 1<<CS10 | 1<<CS12 | 1<<WGM12; // set 1024 prescaler and CTC mode
	TIMSK1 |= 1<<OCIE1A; // enable interrupt for compare match
	sei(); // enable global interupts
}

int main(void)
{
	DDRB |= 1<<PB1;
	SetTimer1();

	while(1)
	{

	}
}
