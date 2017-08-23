/*
 * AD5752.h
 *
 *  Created on: 22 Aug 2017
 *      Author: Lukas Martisiunas
 */

#ifndef AD5752_H_
#define AD5752_H_
#define slave_pin_DAC 9;

#define p5V 		0 		// +5V
#define p10V 		1 		// +10V
#define p108V  		2 	// +10.8V
#define pn5V 		3 		// +/-5V
#define pn10V 		4		// +/-10V
#define pn108V  	5		// +/-10.8V

#define DAC_A 	0
#define DAC_B 	2
#define DAC_AB 	4

extern char DAC_CS_pin;

void init_DAC(char sel_DAC, char range); //Initialises DAC and powers on. sel_DAC selects which DAC will be powered. range sets the output range. use predefined calls.

void set_DAC_value(unsigned int DAC_value, char DAC); //Sets selected DAC to selected value

#endif /* AD5752_H_ */
