/*
 * BIT_MATH.h
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define MY_SET_BIT(reg,bit_num) (reg |= (1<<bit_num))
#define MY_CLEAR_BIT(reg,bit_num) (reg &= ~(1<<bit_num))
#define MY_TOGGLE_BIT(reg,bit_num) (reg ^= (1<<bit_num))
#define MY_GET_BIT(reg,bit_num) ( ( reg>>bit_num) & 1 )



#endif /* BIT_MATH_H_ */
