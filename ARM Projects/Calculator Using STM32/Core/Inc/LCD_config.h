/*
 * LCD_config.h
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


#define LCD_DATA_PORT GPIOB

#define LCD_DATA_D0 GPIO_PIN_3
#define LCD_DATA_D1 GPIO_PIN_4
#define LCD_DATA_D2 GPIO_PIN_5
#define LCD_DATA_D3 GPIO_PIN_6
#define LCD_DATA_D4 GPIO_PIN_7
#define LCD_DATA_D5 GPIO_PIN_8
#define LCD_DATA_D6 GPIO_PIN_9
#define LCD_DATA_D7 GPIO_PIN_10


#define LCD_RS_PORT GPIOB
#define LCD_RS_PIN GPIO_PIN_14

#define LCD_RW_PORT GPIOB
#define LCD_RW_PIN GPIO_PIN_13

#define LCD_E_PORT GPIOB
#define LCD_E_PIN GPIO_PIN_12


#endif /* LCD_CONFIG_H_ */
