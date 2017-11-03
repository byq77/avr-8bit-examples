/*
 * 74HC595 Shift Register example
 * Copyright (C) 2017 Szymon Szantula
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#include "src/sr_74HC595.h"

#ifdef PROGMEM_TEST
#include <avr/pgmspace.h>
/* this way the array is placed in the program space ( FLASH ) normally it is placed in the SRAM */
const uint8_t led_list[8] PROGMEM = {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18};
#else
const uint8_t led_list[8] = {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18};
#endif

int main(void)
{
	uint8_t index = 0;

	_delay_ms(100); // pin oscillation

	InitShiftRegister();
	EnableOutput();

	while(1)
	{
		if(index > 7)
			index = 0;
#ifdef PROGMEM_TEST
		ShiftDataIn(pgm_read_byte(&led_list[index])); // reading form program memory
#else
		ShiftDataIn(led_list[index]);
#endif
		index++;
		_delay_ms(100);
	}
}
