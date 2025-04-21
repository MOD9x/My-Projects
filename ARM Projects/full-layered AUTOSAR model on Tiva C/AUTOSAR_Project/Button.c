/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.c
 *
 * Description: Source file for Button Module.
 *
 *  Created on: Jul 11, 2024
 *      Author: mod_n
 ******************************************************************************/
#include "Dio.h"
#include "Port.h"
#include "Button.h"

/* Global variable to hold the button state */
static uint8 g_button_state = BUTTON_RELEASED;

/*******************************************************************************************************************/
void Button_Init(void)
{
    Port_SetPinDirection( PortConf_SW1_PORT_ID_INDEX,
                          PortConf_SW1_PIN_DIR_NUM
                           );

    Port_SetPinMode( PortConf_SW1_PORT_ID_INDEX ,
                     PortConf_SW1_PIN_MODE_NUM );
}

/*******************************************************************************************************************/
uint8 Button_GetState(void)
{
    return g_button_state;
}

/*******************************************************************************************************************/
void Button_RefreshState(void)
{
    uint8 state = Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX);

    /* Count the number of Pressed times increment if the switch pressed for 20 ms */
    static uint8 g_Pressed_Count  = 0;

    /* Count the number of Released times increment if the switch released for 20 ms */
    static uint8 g_Released_Count = 0;

    if(state == BUTTON_PRESSED)
    {
        g_Pressed_Count++;
        g_Released_Count = 0;
    }
    else
    {
        g_Released_Count++;
        g_Pressed_Count = 0;
    }

    if(g_Pressed_Count == 3)
    {
        g_button_state = BUTTON_PRESSED;
        g_Pressed_Count       = 0;
        g_Released_Count      = 0;
    }
    else if(g_Released_Count == 3)
    {
        g_button_state = BUTTON_RELEASED;
        g_Released_Count      = 0;
        g_Pressed_Count       = 0;
    }
}
/*******************************************************************************************************************/
