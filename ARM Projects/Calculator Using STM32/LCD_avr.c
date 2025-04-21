/*
 * LCD_avr.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#define F_CPU 16000000ul
#include"DIO.h"
#include<stdint.h>
#include<util/delay.h>
#include"BIT_MATH.h"
#include"LCD_avr.h"
#include"LCD_config.h"




void LCD_sendData(uint8_t data)
{
	DIO_SetPortValue(LCD_DATA_PORT,data);
//	send data
	_delay_ms(10);

	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	//	register selector ( data:high / command:low )

	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
//  R/W ( read : low /write:high )

	_delay_ms(10);

	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
//  Enable ( pulse falling edge)

}

void LCD_sendinst(uint8_t inst)
{
	DIO_SetPortValue(LCD_DATA_PORT,inst);
	//	send data
	_delay_ms(1);
	DIO_SetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
	//	register selector ( data:high / command:low )
	_delay_ms(1);
	DIO_SetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
	//  R/W ( read : low /write:high )
	_delay_ms(1);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_E_PORT,LCD_E_PIN,LOW);
	//  Enable ( pulse falling edge)
	_delay_ms(1);


}

void LCD_Init(void)
{
	DIO_SetPortDrirection(LCD_DATA_PORT,0xFF);

	DIO_SetPinDrirection(LCD_RS_PORT,LCD_RS_PIN,output);
	DIO_SetPinDrirection(LCD_RW_PORT,LCD_RW_PIN,output);
	DIO_SetPinDrirection(LCD_E_PORT,LCD_E_PIN,output);
	_delay_ms(40);

	LCD_sendinst(LCD_TWO_LINES_EIGHT_BITS_MODE);
	// Function Set P.19
	_delay_ms(1);

	LCD_sendinst(LCD_CURSOR_ON_BLINK);
	// Display ON/OFF p.18
	_delay_ms(1);

	LCD_sendinst(LCD_CLEAR_COMMAND);
	// set entry mode p.17

}

void LCD_DisplayString(uint8_t const *str)
{
	while( *str != '\0')
	{
		LCD_sendData( (*str++) );
	}
}

void LCD_sendNumber(uint64_t number)
{
	uint8_t i=0;
	uint64_t number_askii[20] ={0} ;

	if(number == 0)
	{
		LCD_sendData('0');
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
	/* Move the LCD cursor to this specific address */
	LCD_sendinst(pos | LCD_SET_CURSOR_LOCATION);
}
