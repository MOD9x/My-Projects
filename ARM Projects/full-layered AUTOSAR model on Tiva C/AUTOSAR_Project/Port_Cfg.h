/*
 * Port_Cfg.h
 *
 *  Created on: Jul 11, 2024
 *      Author: mod_n
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include "Port.h"
#include "Button.h"

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Number of the configured Pins */
#define PORT_CONFIGURED_PINS              (2U)

/* Port Index in the array of structures in Port_PBcfg.c */
#define PortConf_LED1_PORT_ID_INDEX        (uint8)0x00
#define PortConf_SW1_PORT_ID_INDEX         (uint8)0x01

/* Port Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                (Port_PortType)5 /* PORTF */
#define PortConf_SW1_PORT_NUM                 (Port_PortType)5 /* PORTF */

/* Port Configured Pin ID's */
#define PortConf_LED1_PIN_NUM             (Port_PinType)1 /* Pin 1 in PORTF */
#define PortConf_SW1_PIN_NUM              (Port_PinType)4 /* Pin 4 in PORTF */

/* Port Configured Pin modes ID's */
#define PortConf_LED1_PIN_MODE_NUM             (Port_PinModeType)(GPIO) /* Pin 1 in PORTF is GPIO */
#define PortConf_SW1_PIN_MODE_NUM              (Port_PinModeType)(GPIO) /* Pin 4 in PORTF is GPIO */


/* Port Configured Pin direction ID's */
#define PortConf_LED1_PIN_DIR_NUM             (Port_PinDirectionType)(PORT_PIN_OUT) /* Pin 1 in PORTF is o/p */
#define PortConf_SW1_PIN_DIR_NUM              (Port_PinDirectionType)(PORT_PIN_IN) /* Pin 4 in PORTF is i/p */

/* Port Configured Pin internal resistor ID's */
#define PortConf_LED1_PIN_RES_NUM             (Port_InternalResistor)(OFF) /* Pin 1 in PORTF internal resistor is Disable   */
#define PortConf_SW1_PIN_RES_NUM              (Port_InternalResistor)(PULL_UP) /* Pin 4 in PORTF Internal pull up is Enabled  */

/* Port Configured Pin initial value ID's */
#define PortConf_LED1_PIN_IV_NUM             (Port_InitValue)(STD_LOW) /* Pin 1 in PORTF internal resistor is Disable   */
#define PortConf_SW1_PIN_IV_NUM              (Port_InitValue)(STD_HIGH) /* Pin 4 in PORTF Internal pull up is Enabled  */

#endif /* PORT_CFG_H_ */
