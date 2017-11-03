/*
 * 74HC595 Shift Register example
 * Copyright (C) 2017 Szymon Szantula
 *
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */
#ifndef PIN_CONFIG_H_
#define PIN_CONFIG_H_

#define SHIFTREG_PORT PORTD ///< Shift Register Port
#define SHIFTREG_DDR DDRD ///< Shift Register Data Direction Register
#define SCLR PD6 ///< Shift Register Clock Input
#define SCK PD5 ///< Shift Register Clock Input
#define RCK PD4 ///< Storage Register Clock Input
#define G PD3 ///< Output Enable Input
#define SI PD2 ///< Serial Data Input

#endif /* PIN_CONFIG_H_ */
