/*
 * parsecommands.h
 *
 *  Created on: 22 Oct 2017
 *      Author: svr11
 */

#ifndef PARSECOMMANDS_H_
#define PARSECOMMANDS_H_

#include "UART.h"
#include "motorfuncs.h"
#include "ADC.h"
#include "GPIO.h"

/****Variable declarations****/
char Command[MAX_BUF], TargetMotor[MAX_BUF], ExternObj[MAX_BUF],Direction[MAX_BUF];
uint32_t adc_value;uint32_t adc_value2 ;uint32_t adc_value3 ;

/****Function declarations****/
void parse_command(char Command[MAX_BUF],char TargetMotor[MAX_BUF], char ExternObj[MAX_BUF],int NoSteps);
void parse_commandSeq(char Command[MAX_BUF],char ExternObj[MAX_BUF],int Val);

#endif /* PARSECOMMANDS_H_ */
