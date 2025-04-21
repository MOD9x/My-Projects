/*
 * DIO.c
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#include<avr/io.h>
#include<stdint.h>
#include"BIT_MATH.h"
#include"DIO.h"


ERR_T DIO_SetPinDrirection(PORT_T port , PIN_T pin , DIR_T dir)
{
	ERR_T status = OK;

	if( pin <= PIN_7)
	{
		if( dir == input)
		{
			switch(port)
			{
			case PORT_A : CLEAR_BIT(DDRA,pin) ;break;
			case PORT_B : CLEAR_BIT(DDRB,pin) ;break;
			case PORT_C : CLEAR_BIT(DDRC,pin) ;break;
			case PORT_D : CLEAR_BIT(DDRD,pin) ;break;
			default : 		status = NOK;
			}
		}

		else if(dir == output)
		{
			switch(port)
			{
			case PORT_A : SET_BIT(DDRA,pin);break;
			case PORT_B : SET_BIT(DDRB,pin);break;
			case PORT_C : SET_BIT(DDRC,pin);break;
			case PORT_D : SET_BIT(DDRD,pin);break;
			default : 		status = NOK;
			}
		}

		else
		{
		status = NOK;
		}

	}

	else
	{
		status = NOK;
	}

	return status;

}

ERR_T DIO_SetPinValue(PORT_T port , PIN_T pin , VAL_T val)
{
	ERR_T status = OK;

	if( pin <= PIN_7)
	{
		if( val == LOW)
		{
			switch(port)
			{
			case PORT_A : CLEAR_BIT(PORTA,pin) ;break;
			case PORT_B : CLEAR_BIT(PORTB,pin) ;break;
			case PORT_C : CLEAR_BIT(PORTC,pin) ;break;
			case PORT_D : CLEAR_BIT(PORTD,pin) ;break;
			default : 		status = NOK;
			}
		}

		else if(val == HIGH)
		{
			switch(port)
			{
			case PORT_A : SET_BIT(PORTA,pin);break;
			case PORT_B : SET_BIT(PORTB,pin);break;
			case PORT_C : SET_BIT(PORTC,pin);break;
			case PORT_D : SET_BIT(PORTD,pin);break;
			default : 		status = NOK;
			}
		}

		else
		{
		status = NOK;
		}

	}

	else
	{
		status = NOK;
	}

	return status;

}

ERR_T DIO_GetPinValue(PORT_T port , PIN_T pin , uint8_t* val)
{
	ERR_T status = OK;

	if( pin <= PIN_7)
	{
			switch(port)
			{
			case PORT_A : *val = GET_BIT(PINA,pin) ;break;
			case PORT_B : *val = GET_BIT(PINB,pin) ;break;
			case PORT_C : *val = GET_BIT(PINC,pin) ;break;
			case PORT_D : *val = GET_BIT(PIND,pin) ;break;
			default : 		status = NOK;
			}

	}

	else
	{
		status = NOK;
	}

	return status;

}

ERR_T DIO_SetPortDrirection(PORT_T port , uint8_t dir)
{
	ERR_T status = OK;

	if( port <= PORT_D)
	{
		if( dir <= 0xFF)
		{
			switch(port)
			{
			case PORT_A : DDRA = dir ;break;
			case PORT_B : DDRB = dir ;break;
			case PORT_C : DDRC = dir ;break;
			case PORT_D : DDRD = dir ;break;
			default : 		status = NOK;
			}
		}

		else
		{
		status = NOK;
		}

	}

	else
	{
		status = NOK;
	}

	return status;

}

ERR_T DIO_SetPortValue(PORT_T port , uint8_t val)
{
	ERR_T status = OK;

	if( port <= PORT_D)
	{
		if( val <= 0xFF)
		{
			switch(port)
			{
			case PORT_A : PORTA = val ;break;
			case PORT_B : PORTB = val ;break;
			case PORT_C : PORTC = val ;break;
			case PORT_D : PORTD = val ;break;
			default : 		status = NOK;
			}
		}

		else
		{
		status = NOK;
		}

	}

	else
	{
		status = NOK;
	}

	return status;

}

ERR_T DIO_GetPortValue(PORT_T port , uint8_t* val )
{
	ERR_T status = OK;

	switch(port)
			{
			case PORT_A : *val = PINA ;break;
			case PORT_B : *val = PINB ;break;
			case PORT_C : *val = PINC ;break;
			case PORT_D : *val = PIND ;break;
			default : 		status = NOK;
			}

	return status;


}

ERR_T DIO_EnablePullup(PORT_T port , PIN_T pin )
{
	ERR_T status = OK;

	if( pin <= PIN_7)
	{
		switch(port)
			{
			case PORT_A : SET_BIT(PORTA,pin);break;
			case PORT_B : SET_BIT(PORTB,pin);break;
			case PORT_C : SET_BIT(PORTC,pin);break;
			case PORT_D : SET_BIT(PORTD,pin);break;
			default : 		status = NOK;
			}
	}

	else
	{
		status = NOK;
	}

	return status;

}
