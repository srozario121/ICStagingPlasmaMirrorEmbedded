/*
 * GPIO.c
 *
 *  Created on: 16 Oct 2017
 *      Author: svr11
 */

#include "GPIO.h"
//#include "derivative.h" /* include peripheral declarations */


/**********************************************************************************************
* External objects
**********************************************************************************************/

/**********************************************************************************************
* Global variables
**********************************************************************************************/


/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/


/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/

/***********************************************************************************************
*
* @brief    GPIO_Init - Initiates the GPIO pins
*
* @param    Channel to init and resolution
* @return   none
*
************************************************************************************************/
void GPIO_Init()
{
	CONFIG_PIN_AS_GPIO(H1,PTH0,OUTPUT); 		/* Configure RED LED as an output */
	CONFIG_PIN_AS_GPIO(H1,PTH1,OUTPUT); 		/* Configure GREEN LED as an output */
	CONFIG_PIN_AS_GPIO(E1,PTE7,OUTPUT); 		/* Configure BLUE LED as an output */

	CONFIG_PIN_AS_GPIO(E1,PTE4,INPUT); 			/* Configure BTN0 as an input */
	CONFIG_PIN_AS_GPIO(E1,PTE5,INPUT); 			/* Configure BTN1 as an input */
	ENABLE_INPUT(E1,PTE4);			 			/* Enable input BTN0*/
	ENABLE_INPUT(E1,PTE5);						/* Enable input BTN1*/

	LED0_OFF;									/* Turn off RED */
	LED1_OFF;									/* Turn off GREEN */
	LED2_OFF;									/* Turn off BLUE */


//MS1
	CONFIG_PIN_AS_GPIO(E1,PTE0,OUTPUT); 		/* Configure GPIO PTE0 as an output */
	CONFIG_PIN_AS_GPIO(E1,PTE1,OUTPUT); 		/* Configure GPIO PTE1 as an output */
	CONFIG_PIN_AS_GPIO(E1,PTE2,OUTPUT); 		/* Configure GPIO PTE2 as an output */
	CONFIG_PIN_AS_GPIO(E1,PTE3,OUTPUT); 		/* Configure GPIO PTE3 as an output */

//MS2
	CONFIG_PIN_AS_GPIO(C1,PTC5,OUTPUT); 		/* Configure GPIO PTC5 as an output */
	CONFIG_PIN_AS_GPIO(E1,PTE6,OUTPUT); 		/* Configure GPIO PTE6 as an output */
	CONFIG_PIN_AS_GPIO(H1,PTH6,OUTPUT); 		/* Configure GPIO PTH6 as an output */
	CONFIG_PIN_AS_GPIO(H1,PTH7,OUTPUT); 		/* Configure GPIO PTH7 as an output */

//MT1
	CONFIG_PIN_AS_GPIO(I1,PTI4,OUTPUT); 		/* Configure GPIO PTI4 as an output */
	CONFIG_PIN_AS_GPIO(I1,PTI5,OUTPUT); 		/* Configure GPIO PTI5 as an output */
	CONFIG_PIN_AS_GPIO(I1,PTI6,OUTPUT); 		/* Configure GPIO PTI6 as an output */
	CONFIG_PIN_AS_GPIO(H1,PTH5,OUTPUT); 		/* Configure GPIO PTH5 as an output */

//MT2
	CONFIG_PIN_AS_GPIO(G1,PTG3,OUTPUT); 		/* Configure GPIO PTG3 as an output */
	CONFIG_PIN_AS_GPIO(G1,PTG2,OUTPUT); 		/* Configure GPIO PTG2 as an output */
	CONFIG_PIN_AS_GPIO(G1,PTG1,OUTPUT); 		/* Configure GPIO PTG1 as an output */
	CONFIG_PIN_AS_GPIO(G1,PTG0,OUTPUT); 		/* Configure GPIO PTG0 as an output */

//MS1
	MS1STEP_OFF;									/*GPIO PTE0 to low*/
	MS1COMM_OFF;									/*GPIO PTE1 to low*/
	MS1DIR_OFF;									/*GPIO PTE2 to low*/
	MS1DISABLE_OFF;									/*GPIO PTE3 to low*/

//MS2
	MS2STEP_OFF;									/*GPIO PTE0 to low*/
	MS2COMM_OFF;									/*GPIO PTE1 to low*/
	MS2DIR_OFF;									/*GPIO PTE2 to low*/
	MS2DISABLE_OFF;									/*GPIO PTE3 to low*/
//MT1
	MT1STEP_OFF;									/*GPIO PTE0 to low*/
	MT1COMM_OFF;									/*GPIO PTE1 to low*/
	MT1DIR_OFF;									/*GPIO PTE2 to low*/
	MT1DISABLE_OFF;									/*GPIO PTE3 to low*/

//MT2
	MT2STEP_OFF;									/*GPIO PTE0 to low*/
	MT2COMM_OFF;									/*GPIO PTE1 to low*/
	MT2DIR_OFF;									/*GPIO PTE2 to low*/
	MT2DISABLE_OFF;									/*GPIO PTE3 to low*/

	return;
}

