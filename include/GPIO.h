/*
 * GPIO.h
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "derivative.h"
/*
 * Macros for pin definitions
 * */
#define A1  A
#define B1  A
#define C1  A
#define D1  A

#define E1	B
#define F1	B
#define G1	B
#define H1	B

#define I1	C

#define OUTPUT  1
#define INPUT	0

//LED and Buttons pins
#define PTH0 24 								/* For RED LED */
#define PTH1 25 								/* For GREEN LED */
#define PTE7 7  								/* For BLUE LED */
#define PTE4 4  								/* For SW2 - BTN0 */
#define PTE5 5  								/* For SW3 - BTN1 */

//Motor GPIOs
//MS1
#define PTE0 0									/*GPIO- Motor A*/
#define PTE1 1									/*GPIO- Motor B*/
#define PTE2 2									/*GPIO- Motor C*/
#define PTE3 3									/*GPIO- Motor D*/
//MS2
#define PTC5 21									/*GPIO- Motor A*/
#define PTE6 6									/*GPIO- Motor B*/
#define PTH6 30									/*GPIO- Motor C*/
#define PTH7 31									/*GPIO- Motor D*/
//MT1
#define PTI4 4									/*GPIO- Motor A*/
#define PTI5 5									/*GPIO- Motor B*/
#define PTI6 6									/*GPIO- Motor C*/
#define PTH5 29									/*GPIO- Motor D*/
//MT2
#define PTG3 19									/*GPIO- Motor A*/
#define PTG2 18									/*GPIO- Motor B*/
#define PTG1 17									/*GPIO- Motor C*/
#define PTG0 16									/*GPIO- Motor D*/

/*
 * GPIO configuration macros
 * */
#define CONFIG_PIN_AS_GPIO(port,port_pin,mode)    XCONFIG_PIN_AS_GPIO(port,port_pin,mode)
#define XCONFIG_PIN_AS_GPIO(port,port_pin,mode)   (mode == 0) ? (GPIO##port##_PDDR |= 0 << port_pin) : (GPIO##port##_PDDR |= 1 << port_pin)

#define ENABLE_INPUT(port,port_pin) 				XENABLE_INPUT(port,port_pin)
#define XENABLE_INPUT(port,port_pin)				GPIO##port##_PIDR ^= 1<<port_pin

#define ENABLE_PULLUP(port,port_pin) 				XENABLE_PULLUP(port,port_pin) 	
#define XENABLE_PULLUP(port,port_pin) 				PORT_PUE0 |= PORT_PUE0_PT##port##PE##port_pin##_MASK

#define OUTPUT_SET(port,register_num)				XOUTPUT_SET(port,register_num)
#define XOUTPUT_SET(port,register_num)				GPIO##port##_PCOR |=1<<register_num

#define OUTPUT_CLEAR(port,register_num)				XOUTPUT_CLEAR(port,register_num)		
#define XOUTPUT_CLEAR(port,register_num)			GPIO##port##_PSOR |=1<<register_num

#define OUTPUT_TOGGLE(port,register_num)			XOUTPUT_TOGGLE(port,register_num)
#define XOUTPUT_TOGGLE(port,register_num)			GPIO##port##_PTOR |=1<<register_num
												
#define CONFIG_PIN_AS_FGPIO(port,port_pin,mode)    XCONFIG_PIN_AS_FGPIO(port,port_pin,mode)
#define XCONFIG_PIN_AS_FGPIO(port,port_pin,mode)   (mode == 0) ? (FGPIO##port##_PDDR |= 0 << port_pin) : (FGPIO##port##_PDDR |= 1 << port_pin)

#define READ_INPUT(port,port_pin)					XREAD_INPUT(port,port_pin)
#define XREAD_INPUT(port,port_pin)					(GPIO##port##_PDIR & GPIO_PDIR_PDI(1<<port_pin))

/*
 * Shortcuts for pin control
 * MS1- Motor spooler 1
 * MS2- Motor spooler 2
 * MT1- Motor tractor 1
 * MT2- Motor tractor 2
 * COMM-Common ground
 * STEP-Stepping pin for bipolar motor. Controls logic for motor
 * DIR- Controls the direction of rotation for the motor
 * DISABLE- Sets Motor current to 0
 * */

//LED macros
#define LED0_TOGGLE		OUTPUT_TOGGLE(H1,PTH0);
#define LED1_TOGGLE		OUTPUT_TOGGLE(H1,PTH1);
#define LED2_TOGGLE		OUTPUT_TOGGLE(E1,PTE7);

#define LED0_OFF		OUTPUT_CLEAR(H1,PTH0);
#define LED1_OFF		OUTPUT_CLEAR(H1,PTH1);
#define LED2_OFF		OUTPUT_CLEAR(E1,PTE7);

#define LED0_ON			OUTPUT_SET(H1,PTH0);
#define LED1_ON			OUTPUT_SET(H1,PTH1);
#define LED2_ON			OUTPUT_SET(E1,PTE7);

//Motor control macros
//MS1

#define MS1COMM_ON		OUTPUT_CLEAR(E1,PTE3);
#define MS1STEP_ON		OUTPUT_CLEAR(E1,PTE2);
#define MS1DIR_ON		OUTPUT_CLEAR(E1,PTE1);
#define MS1DISABLE_ON		OUTPUT_CLEAR(E1,PTE0);

#define MS1COMM_OFF		OUTPUT_SET(E1,PTE3);
#define MS1STEP_OFF		OUTPUT_SET(E1,PTE2);
#define MS1DIR_OFF		OUTPUT_SET(E1,PTE1);
#define MS1DISABLE_OFF		OUTPUT_SET(E1,PTE0);


#define MS1COMM_TOGGLE		OUTPUT_TOGGLE(E1,PTE3);
#define MS1STEP_TOGGLE		OUTPUT_TOGGLE(E1,PTE2);
#define MS1DIR_TOGGLE		OUTPUT_TOGGLE(E1,PTE1);
#define MS1DISABLE_TOGGLE		OUTPUT_TOGGLE(E1,PTE0);

//MS2 PTC5 PTE6 PTH6 PTH7
#define MS2COMM_ON		OUTPUT_CLEAR(H1,PTH7);
#define MS2STEP_ON		OUTPUT_CLEAR(H1,PTH6);
#define MS2DIR_ON		OUTPUT_CLEAR(E1,PTE6);
#define MS2DISABLE_ON		OUTPUT_CLEAR(C1,PTC5);

#define MS2COMM_OFF		OUTPUT_SET(H1,PTH7);
#define MS2STEP_OFF		OUTPUT_SET(H1,PTH6);
#define MS2DIR_OFF		OUTPUT_SET(E1,PTE6);
#define MS2DISABLE_OFF		OUTPUT_SET(C1,PTC5);


#define MS2COMM_TOGGLE		OUTPUT_TOGGLE(H1,PTH7);
#define MS2STEP_TOGGLE		OUTPUT_TOGGLE(H1,PTH6);
#define MS2DIR_TOGGLE		OUTPUT_TOGGLE(E1,PTE6);
#define MS2DISABLE_TOGGLE		OUTPUT_TOGGLE(C1,PTE0);
//MT1 PTI4 PTI5 PTI6 PTH5
#define MT1COMM_ON		OUTPUT_CLEAR(H1,PTH5);
#define MT1STEP_ON		OUTPUT_CLEAR(I1,PTI6);
#define MT1DIR_ON		OUTPUT_CLEAR(I1,PTI5);
#define MT1DISABLE_ON		OUTPUT_CLEAR(I1,PTI4);

#define MT1COMM_OFF		OUTPUT_SET(H1,PTH5);
#define MT1STEP_OFF		OUTPUT_SET(I1,PTI6);
#define MT1DIR_OFF		OUTPUT_SET(I1,PTI5);
#define MT1DISABLE_OFF		OUTPUT_SET(I1,PTI4);


#define MT1COMM_TOGGLE		OUTPUT_TOGGLE(H1,PTH5);
#define MT1STEP_TOGGLE		OUTPUT_TOGGLE(I1,PTI6);
#define MT1DIR_TOGGLE		OUTPUT_TOGGLE(I1,PTI5);
#define MT1DISABLE_TOGGLE		OUTPUT_TOGGLE(I1,PTI4);
//MT2 PTG3 PTG2 PTG1 PTG0
#define MT2COMM_ON		OUTPUT_CLEAR(G1,PTG0);
#define MT2STEP_ON		OUTPUT_CLEAR(G1,PTG1);
#define MT2DIR_ON		OUTPUT_CLEAR(G1,PTG2);
#define MT2DISABLE_ON		OUTPUT_CLEAR(G1,PTG3);

#define MT2COMM_OFF		OUTPUT_SET(G1,PTG0);
#define MT2STEP_OFF		OUTPUT_SET(G1,PTG1);
#define MT2DIR_OFF		OUTPUT_SET(G1,PTG2);
#define MT2DISABLE_OFF		OUTPUT_SET(G1,PTG3);


#define MT2COMM_TOGGLE		OUTPUT_TOGGLE(G1,PTG0);
#define MT2STEP_TOGGLE		OUTPUT_TOGGLE(G1,PTG1);
#define MT2DIR_TOGGLE		OUTPUT_TOGGLE(G1,PTG2);
#define MT2DISABLE_TOGGLE		OUTPUT_TOGGLE(G1,PTG3);

/*
 * External variables
 * */

/*
 * Function declarations
 * */
void GPIO_Init();

#endif /* GPIO_H_ */
