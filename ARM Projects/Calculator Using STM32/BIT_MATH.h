/*
 * BIT_MATH.h
 *
 *  Created on: Sep 5, 2024
 *      Author: mod_n
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(reg,bit_num) (reg |= (1<<bit_num))
#define CLEAR_BIT(reg,bit_num) (reg &= ~(1<<bit_num))
#define TOGGLE_BIT(reg,bit_num) (reg ^= (1<<bit_num))
#define GET_BIT(reg,bit_num) ( ( reg>>bit_num) & 1 )



#endif /* BIT_MATH_H_ */
