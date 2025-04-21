/*
 * LCD_STM32.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#include"stm32f1xx_hal.h"
#include<stdint.h>
#include"BIT_MATH.h"
#include"LCD_STM32.h"
#include"LCD_config.h"

uint16_t LCD_data[8] = { LCD_DATA_D0 ,
		                 LCD_DATA_D1 ,
		                 LCD_DATA_D2 ,
		                 LCD_DATA_D3 ,
		                 LCD_DATA_D4 ,
		                 LCD_DATA_D5 ,
		                 LCD_DATA_D6 ,
		                 LCD_DATA_D7
};


void LCD_sendData(uint8_t data)
{
	uint8_t i=0;

	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_data[i] , ( (data>>(i))&0x01  ) );

	}

//	send data
	HAL_Delay(10);

	HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, 1 );
	//	register selector ( data:high / command:low )

	HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, 0 );
//  R/W ( read : low /write:high )

	HAL_Delay(10);

	HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 1 );
	HAL_Delay(10);

	HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 0 );
	HAL_Delay(10);

//  Enable ( pulse falling edge)

}

void LCD_sendinst(uint8_t inst)
{
	uint8_t i=0;

	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_data[i] , ( (inst>>(i))&0x01  ) );

	}

	//	send data
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, 0 );
	//	register selector ( data:high / command:low )
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, 0 );
	//  R/W ( read : high /write:low )
	HAL_Delay(1);

	HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 1 );

	HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 0 );
	//  Enable ( pulse falling edge)



}

void LCD_Init(void)
{
	HAL_Delay(40);
	// Function Set P.19
	LCD_sendinst(LCD_TWO_LINES_EIGHT_BITS_MODE);


	// Display ON/OFF p.18
	LCD_sendinst(LCD_CURSOR_ON_BLINK);

	HAL_Delay(1);

	// set entry mode p.17
	LCD_sendinst(LCD_CLEAR_COMMAND);

	HAL_Delay(1);


}

void LCD_DisplayString(uint8_t const *str)
{
	while( *str != '\0')
	{
		LCD_sendData( (*str++) );
	}
}

void LCD_sendNumber(int64_t number)
{
	uint8_t i=0;
	uint64_t number_askii[20] ={0} ;

	if(number == 0)
	{
		LCD_sendData('0');
	}
	else if(number < 0)
	{
		LCD_sendData('-');
		number = number * (-1);
	}

	while( number != 0 )
	{
		i++;
		number_askii[i] = (number%10 ) +48 ;
		number /=10;
	}
	while( i != 0 )
	{
		LCD_sendData(number_askii[i]);
		i--;
	}
}

void LCD_GoToPos(uint8_t x ,uint8_t y)
{
	uint8_t pos=0;

	switch(y)
	{
		 case 0:
			pos=x;
				break;
		 case 1:
			pos=x+0x40;
				break;
		 case 2:
			pos=x+0x10;
				break;
		 case 3:
			pos=x+0x50;
				break;

	}
/*	 Move the LCD cursor to this specific address*/
	LCD_sendinst(pos | LCD_SET_CURSOR_LOCATION);
}
