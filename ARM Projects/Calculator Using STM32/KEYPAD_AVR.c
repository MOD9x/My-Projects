/*
 * KEYPAD_AVR.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#include"DIO.h"
#include<stdint.h>
#include<util/delay.h>
#include"BIT_MATH.h"
#include"KEYPAD_avr.h"
#include"KEYPAD_config.h"


void Keypad_Init(void)
{
	uint8_t pin_counter =0 ;

	for(pin_counter=0;pin_counter<KEYPAD_ROW;pin_counter++)
	{
		DIO_SetPinDrirection(KPAD_ROW_PORT,KPAD_ROW_PIN0+pin_counter,input);
		DIO_EnablePullup(KPAD_ROW_PORT,KPAD_ROW_PIN0+pin_counter);
	}
	//row input
	//row set pullup


	for(pin_counter=0;pin_counter<KEYPAD_COL;pin_counter++)
	{
		DIO_SetPinDrirection(KPAD_COL_PORT,KPAD_COL_PIN0+pin_counter,output);
		DIO_SetPinValue(KPAD_COL_PORT,KPAD_COL_PIN0+pin_counter,HIGH);
	}
	// col config o/p
	// col set high
}

uint8_t Ketpad_GetKey(void)
{
	uint8_t col,row,key;
	while(1)
	{
		for(col=0;col<KEYPAD_COL;col++)
		{
			// for set col 0-3 low
			DIO_SetPinValue(KPAD_COL_PORT,col+KPAD_COL_PIN0,LOW);
			for(row=0;row<KEYPAD_ROW;row++)
			{
					//for read row0-3
				DIO_GetPinValue(KPAD_ROW_PORT,row,&key);
				if(key == LOW)
				{
					return Keys[( col + (4*row) )];
				}

			}
			DIO_SetPinValue(KPAD_COL_PORT,col+KPAD_COL_PIN0,HIGH);
		}
	}
	return 0;

}
