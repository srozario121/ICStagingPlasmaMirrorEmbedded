/*
 * UART.h
 *
 *  Created on: Dec 18, 2013
 *      Author: B46911
 */

#ifndef UART_H_
#define UART_H_
/*******************************************************************************
* Includes
********************************************************************************/
#include "derivative.h"


/*******************************************************************************
* Constants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/
#define MAX_BUF 64

extern char buffer[];
extern int sofar;
extern int parsedone;

                
/*******************************************************************************
* Types
********************************************************************************/


/*******************************************************************************
* Variables
********************************************************************************/


/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/

void init_UART2();


/***********************************************************************************************
*
* @brief    UART_Init - Initalizes the Uart 1 to run at 9600 bauds assuming bus clock of 20Mhz
* @param    none
* @return   none
*
************************************************************************************************/  
void UART_Init();


/***********************************************************************************************
*
* @brief    UART_SendChar - Send a single byte on Uart1
* @param    byte to send
* @return   none
*
************************************************************************************************/  
void UART_SendChar(uint8_t send);

/***********************************************************************************************
*
* @brief    UART_GetChar - Retrieve the received char from the Uart1 buffer (should be called from Interrupt)
* @param    none
* @return   received byte
*
************************************************************************************************/
uint8_t UART_GetChar();

/***********************************************************************************************
*
* @brief    UART_SendStr - Print the String on Terminal Window
* @param    String to be sent
* @return   none
*
************************************************************************************************/
void UART_SendStr(char data_string[]);
/***********************************************************************************************
*
* @brief    itoa - Convert integer to string
* @param    pointer to a char
* @return   none
*
************************************************************************************************/

char* itoa_(int, char*, int);

#endif /* UART_H_ */
