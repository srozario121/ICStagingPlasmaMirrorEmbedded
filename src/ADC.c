/*
 * ADC.c
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */



#include "ADC.h"

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
* @brief    ADC_Init - Initiates the Channel to read the value of the ADC channel
* 			 
* @param    Channel to init and resolution
* @return   none
*
************************************************************************************************/  
void ADC_Init(uint8_t channel, uint8_t mode)
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK;				/* Enable bus clock in ADC*/
	ADC_SC3 |= ADC_SC3_ADICLK(0b00);			/* Bus clock selected*/
	ADC_SC3|= ADC_SC3_ADIV(0b11);
	ADC_SC2 |= 0x00;							/* Software Conversion trigger, disable compare function*/
	ADC_SC1 = 0	;								/* Enable ADC by setting ADCH bits as low*/
	ADC_SC1|= ADC_SC1_ADCO_MASK;  				/* Continuous mode operation */
	ADC_SC1|= ADC_SC1_AIEN_MASK;  				/* ADC Interrupt Enabled */
	ADC_APCTL1 |= ADC_APCTL1_ADPC(1<<channel);  /* Channel selection */	
	ADC_SC3 |= ADC_SC3_MODE(mode);				/* 8,10,12 bit mode operation */
}

/***********************************************************************************************
*
* @brief    ADC_Read - Read the selected ADC channel
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
uint16_t ADC_Read(uint8_t channel)
{
	ADC_SC1=0;
	ADC_SC1 |= ADC_SC1_ADCH(channel);			/* Select channel to read */
	while(!(ADC_SC1 & ADC_SC1_COCO_MASK));		/* Wait conversion to complete */
	ADC_SC1=1;
	return ADC_R;								/* Return adc value */
}

uint16_t ADC_StartAcQ(uint8_t channel)
{
	uint16_t Val=ADC_R;
	ADC_SC1 |= ADC_SC1_ADCH(channel);			/* Select channel to read */
	while(!(ADC_SC1 & ADC_SC1_COCO_MASK));		/* Wait conversion to complete */
	Val=ADC_R;
	return Val;								/* Return adc value */
}

void ADC_InitALL()
{
	ADC_Init(ADC_CH0,2);
	ADC_Init(ADC_CH1,2);
	ADC_Init(ADC_CH2,2);
}
