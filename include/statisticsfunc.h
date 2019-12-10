/*
 * statisticsfunc.h
 *
 *  Created on: 20 Oct 2017
 *      Author: svr11
 */

#ifndef STATISTICSFUNC_H_
#define STATISTICSFUNC_H_
#include "ADC.h"

/*Function prototypes*/
double MaxArray(int* InputArray);
float MinArray(int* InputArray);
int MeanArray(int* InputArray);
int StdArray(int* InputArray);
void ZeroArray(int* InputArray);

#endif /* STATISTICSFUNC_H_ */
