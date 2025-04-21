/*
 * m.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#include<avr/io.h>
#include<stdint.h>
#include<util/delay.h>
#include"DIO.h"
#include<stdint.h>
#include"BIT_MATH.h"
#include"LCD_avr.h"
#include"KEYPAD_avr.h"

int main()
{
	uint32_t a=0,b=0,c=0;
	uint8_t	 key=0,switch_flag=0,operation=0,continue_flag=0;
	LCD_Init();
	Keypad_Init();

	while(1)
	{
				key = Ketpad_GetKey();
				LCD_sendData(key);

				switch(key)
				{
				case '=':
							if(continue_flag == 0)
							{
								switch(operation)
										{
										case '-':c=a-b;
										break;

										case '+':c=a+b;
										break;

										case '*':c=a*b;
										break;

										case '/':c=a/b;
										break;
										}
							}

							else
							{
								switch(operation)
									{
									case '-':c=c-b;
									break;

									case '+':c=c+b;
									break;

									case '*':c=c*b;
									break;

									case '/':c=c/b;
									break;
									}
							}

							LCD_sendNumber(c);

							continue_flag=1;
							b=0;

					break;

				case '-':
				case '+':
				case '*':
				case '/':
					switch_flag=1;
					operation=key;

					break;
				case 'x':
							  switch_flag=0;
							  continue_flag=0;
							  c=0;
							  a=0;
							  b=0;
							  LCD_sendinst(LCD_CLEAR_COMMAND);

						break;

				default:
					if(switch_flag == 0)
						{
						a = ( ( ( a )* 10 ) + ( key - 48 ) );
						}
					else
					{
						b = ( ( ( b )* 10 ) + ( key - 48 ) );
					}

					break;
				}
				_delay_ms(4000);

	}
}

