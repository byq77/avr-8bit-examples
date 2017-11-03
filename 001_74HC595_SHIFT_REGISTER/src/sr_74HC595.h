/*
 * 74HC595 Shift Register example
 * Copyright (C) 2017 Szymon Szantula
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#ifndef SR_74HC595_H_
#define SR_74HC595_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/sfr_defs.h>
#include "pin_config.h"

extern volatile uint8_t data; ///< data byte that is wirtten to the shift register

extern volatile uint8_t bit_count; ///< variable updated by isr

/**
 * @brief Initialise outputs, variables and timer0.
 */
void InitShiftRegister();

/**
 * @brief Shift data to the register.
 *
 * @param input_data a byte of data to be shift in
 */
void ShiftDataIn(uint8_t input_data);

/**
 * @brief Enable sr's 3-state buffor output.
 */
void EnableOutput();

/**
 * @brief Disable sr's 3-state buffor output ( high impedance ).
 */
void DisableOutput();

/**
 * @brief Clear sr's input register.
 */
void ClearRegister();

#endif /* SR_74HC595_H_ */
