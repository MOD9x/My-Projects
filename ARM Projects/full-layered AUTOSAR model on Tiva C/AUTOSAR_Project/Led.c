/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 *  Created on: Jul 11, 2024
 *      Author: mod_n
 ******************************************************************************/
#include "Port.h"
#include "Dio.h"
#include "Led.h"

/*********************************************************************************************/
void Led_Init(void)
{
    Port_SetPinDirection( PortConf_LED1_PORT_ID_INDEX,
                          PortConf_LED1_PIN_DIR_NUM
                           );

    Port_SetPinMode( PortConf_LED1_PORT_ID_INDEX ,
                     PortConf_LED1_PIN_MODE_NUM );
}
/*********************************************************************************************/
void Led_SetOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/*********************************************************************************************/
void Led_SetOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/*********************************************************************************************/
void Led_RefreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* re-write the same value */
}

/*********************************************************************************************/
void Led_Toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

/*********************************************************************************************/
