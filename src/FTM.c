/*
 * FTM.c
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */

#include "FTM.h"

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


/**********************************************************************************************
* Global functions
**********************************************************************************************/

/***********************************************************************************************
*
* @brief    FTM0_Init - Initialize the FTM counter and enable 1 interrupt (CH0)
* @param    none
* @return   none
*
************************************************************************************************/
void FTM0_Init_Output_Cmp()
{
	SIM_SCGC |= SIM_SCGC_FTM0_MASK; /* Enable Clock for FTM2 */


	FTM0_SC |= FTM_SC_PS(6);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
								/* Counter increase by one every 6.4 us */

	/* Enable Channle 0*/
	FTM0_C0SC |= FTM_CnSC_CHIE_MASK; /* Enable channel 0 interrupt */
	FTM0_C0SC |= FTM_CnSC_MSA_MASK;  /* Channel as Output compare mode */

	/*Select interrupt frequency*/
	FTM0_C0V = 15620;// This is one interrupt per second
	FTM0_SC |= FTM_SC_CLKS(1); /*FTM2 use system clock*/

}

/***********************************************************************************************
*
* @brief    FTM2_SetPeriod - Set the period of the periodic interrupt
* @param    ch - channel to configure, period - period to set
* @return   none
*
************************************************************************************************/
void FTM0_SetPeriod(int MotorSpeed)
{
//Motor speed is in steps/s
	FTM0_C0V = FTM0_C0V+FTM_CnV_VAL((uint32_t)(15620/MotorSpeed)) ;
}


void FTM0_SetPrescaler(int Prescaler)
{
	FTM0_SC |= FTM_SC_PS(Prescaler);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
}
/***********************************************************************************************
*
* @brief    FTM1_Init - Initialize the FTM1 counter and enable 1 interrupt (CH0)
* @param    none
* @return   none
*
************************************************************************************************/
void FTM1_Init_Output_Cmp()
{
	SIM_SCGC |= SIM_SCGC_FTM1_MASK; /* Enable Clock for FTM2 */


	FTM1_SC |= FTM_SC_PS(6);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
								/* Counter increase by one every 6.4 us */

	/* Enable Channle 0*/
	FTM1_C1SC |= FTM_CnSC_CHIE_MASK; /* Enable channel 0 interrupt */
	FTM1_C1SC |= FTM_CnSC_MSA_MASK;  /* Channel as Output compare mode */

	/*Select interrupt frequency*/
	FTM1_C1V = 15620;// This is one interrupt per second
	FTM1_SC |= FTM_SC_CLKS(1); /*FTM2 use system clock*/

}

/***********************************************************************************************
*
* @brief    FTM1_SetPeriod - Set the period of the periodic interrupt
* @param    ch - channel to configure, period - period to set
* @return   none
*
************************************************************************************************/
void FTM1_SetPeriod(int MotorSpeed)
{
//Motor speed is in steps/s
	FTM1_C1V = FTM1_C1V+FTM_CnV_VAL((uint32_t)(15620/MotorSpeed)) ;
}
/***********************************************************************************************
*
* @brief    FTM1_SetPrescaler - Set the prescaler for the FTM clock
* @param    Prescaler - division of system clock by 2^
* @return   none
*
************************************************************************************************/

void FTM1_SetPrescaler(int Prescaler)
{
	FTM1_SC |= FTM_SC_PS(Prescaler);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
}

/***********************************************************************************************
*
* @brief    FTM2_Init - Initialize the FTM counter and enable 1 interrupt (CH0)
* @param    none
* @return   none
*
************************************************************************************************/
void FTM2_Init_Output_Cmp()
{
	SIM_SCGC |= SIM_SCGC_FTM2_MASK; /* Enable Clock for FTM2 */


	FTM2_SC |= FTM_SC_PS(6);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
								/* Counter increase by one every 6.4 us */

	/* Enable Channle 0*/
	FTM2_C2SC |= FTM_CnSC_CHIE_MASK; /* Enable channel 0 interrupt */
	FTM2_C2SC |= FTM_CnSC_MSA_MASK;  /* Channel as Output compare mode */

	/*Select interrupt frequency*/
	FTM2_C2V = 15620;// This is one interrupt per second
	FTM2_SC |= FTM_SC_CLKS(1); /*FTM2 use system clock*/

}

/***********************************************************************************************
*
* @brief    FTM2_SetPeriod - Set the period of the periodic interrupt
* @param    ch - channel to configure, period - period to set
* @return   none
*
************************************************************************************************/
void FTM2_SetPeriod(int MotorSpeed)
{
//Motor speed is in steps/s
	FTM2_C2V = FTM2_C2V+FTM_CnV_VAL((uint32_t)(15620/MotorSpeed)) ;
}


void FTM2_SetPrescaler(int Prescaler)
{
	FTM2_SC |= FTM_SC_PS(Prescaler);	/* Select Preescaler in this case 128. 20 Mhz /128 =156.25 Khz. */
}


void FTM_Init()
{
	FTM0_Init_Output_Cmp();FTM1_Init_Output_Cmp();FTM2_Init_Output_Cmp();
}
