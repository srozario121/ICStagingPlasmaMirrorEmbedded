/*
 * ADC.h
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */

#ifndef ADC_H_
#define ADC_H_
/*******************************************************************************
* Includes
********************************************************************************/

#include "derivative.h"

	
/*******************************************************************************
* Constants
********************************************************************************/
#define ADC_CH0 8
#define ADC_CH1 9
#define ADC_CH2 12
#define ADC_CH3 13
#define ARRAYLEN 50

/*******************************************************************************
* Macros
********************************************************************************/
#define EIGHT_BIT 	0
#define TEN_BIT 	1
#define TWELVE_BIT 	2
                
/*******************************************************************************
* Types
********************************************************************************/
typedef struct ADCTens{
	int TMeasure;
	int TMin;
	int TMax;
	int TMean;
	int NoValues;
	int Samples;
	int UniqueID;
	uint16_t adc_intialval;
	uint16_t adc_currval;
	uint16_t adc_upperval;
	uint16_t adc_lowerval;
	int ADC_ch;
} ADCTens;

/*******************************************************************************
* Variables
********************************************************************************/
struct ADCTens T1;
struct ADCTens T2;
struct ADCTens T3;

int T1Measure[ARRAYLEN];
int T2Measure[ARRAYLEN];
int T3Measure[ARRAYLEN];
int T1MeanValue,T2MeanValue,T3MeanValue;
int T1StdValue,T2StdValue,T3StdValue;
/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/
/***********************************************************************************************
*
* @brief    ADC_Init - Initiates the Channeln to read the value of the ADC channel
* 			 
* @param    Channel to init and resolution
* @return   none
*
************************************************************************************************/  
void ADC_Init(uint8_t channel, uint8_t mode);

/***********************************************************************************************
*
* @brief    ADC_Read - Read the selected ADC channel
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
uint16_t ADC_Read(uint8_t channel);


void ADC_InitALL();
#endif /* ADC_H_ */
