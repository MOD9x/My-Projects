/*
 * KEYPAD_config.h
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

uint8_t Keys[16]={
		'7','8','9','/',
		'4','5','6','*',
		'1','2','3','-',
		'x','0','=','+'
};

#define KEYPAD_COL 	  4
#define KEYPAD_ROW 	  4

#define KPAD_ROW_PORT PORT_C
#define KPAD_ROW_PIN0 PIN_0
#define KPAD_ROW_PIN1 PIN_1
#define KPAD_ROW_PIN2 PIN_2
#define KPAD_ROW_PIN3 PIN_3

#define KPAD_COL_PORT PORT_C
#define KPAD_COL_PIN0 PIN_4
#define KPAD_COL_PIN1 PIN_5
#define KPAD_COL_PIN2 PIN_6
#define KPAD_COL_PIN3 PIN_7




#endif /* KEYPAD_CONFIG_H_ */
