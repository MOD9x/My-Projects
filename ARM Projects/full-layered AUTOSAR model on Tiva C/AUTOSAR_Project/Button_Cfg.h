/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button_Cfg.h
 *
 * Description: Header file for Pre-Compiler configuration used by Button Module
 *
 *  Created on: Jul 11, 2024
 *      Author: mod_n
 ******************************************************************************/

#ifndef BUTTON_CFG_H_
#define BUTTON_CFG_H_

/* Button State according to its configuration PULL UP/Down */
#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH

/* Set the Button Port */
#define BUTTON_PORT PortConf_SW1_PORT_NUM

/* Set the Button Pin Number */
#define BUTTON_PIN_NUM PortConf_SW1_PIN_NUM


#endif /* BUTTON_CFG_H_ */
