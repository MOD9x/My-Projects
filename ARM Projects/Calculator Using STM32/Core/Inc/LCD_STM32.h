/*
 * LCD_STM32.h
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#ifndef LCD_AVR_H_
#define LCD_AVR_H_

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_CURSOR_ON_BLINK            0x0F
#define LCD_SET_CURSOR_LOCATION        0x80


void LCD_sendData(uint8_t data);
void LCD_sendinst(uint8_t inst);
void LCD_Init(void);
void LCD_DisplayString(uint8_t const *str);
void LCD_sendNumber(int64_t number);
void LCD_GoToPos(uint8_t x ,uint8_t y);



#endif /* LCD_AVR_H_ */
