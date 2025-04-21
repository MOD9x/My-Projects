/*
 * KEYPAD_STM32.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#include"stm32f1xx_hal.h"
#include "KEYPAD_STM32.h"
#include<stdint.h>
#include"BIT_MATH.h"
#include"KEYPAD_config.h"

uint8_t Keys[16]={
		'7','8','9','/',
		'4','5','6','*',
		'1','2','3','-',
		'x','0','=','+'
};

uint16_t cols[KEYPAD_COL] = { KPAD_COL_PIN0,
							  KPAD_COL_PIN1,
							  KPAD_COL_PIN2,
							  KPAD_COL_PIN3
};

uint16_t rows[KEYPAD_ROW] = { KPAD_ROW_PIN0,
							  KPAD_ROW_PIN1,
							  KPAD_ROW_PIN2,
							  KPAD_ROW_PIN3
};

uint8_t Ketpad_GetKey(void)
{
	uint8_t col = 0 ,row = 0 ;

	HAL_GPIO_WritePin(KPAD_COL_PORT,KPAD_COL_PIN0,1);
	HAL_GPIO_WritePin(KPAD_COL_PORT,KPAD_COL_PIN1,1);
	HAL_GPIO_WritePin(KPAD_COL_PORT,KPAD_COL_PIN2,1);
	HAL_GPIO_WritePin(KPAD_COL_PORT,KPAD_COL_PIN3,1);

	while(1)
	{
		for(col=0;col<KEYPAD_COL;col++)
		{
			// for set col 0-3 low
			HAL_GPIO_WritePin(KPAD_COL_PORT, cols[col],0);
			for(row=0;row<KEYPAD_ROW;row++)
			{
					//for read row 0-3
				if(!(HAL_GPIO_ReadPin(KPAD_ROW_PORT,rows[row] )) )
				{
					return Keys[( col + (4*row) )];
				}

			}
			HAL_GPIO_WritePin(KPAD_COL_PORT, cols[col],1);
		}
	}
	return 0;

}

