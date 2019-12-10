
/*
 * UART.c
 *
 *  Created on: Dec 18, 2013
 *      Author: B46911
 */
#include "UART.h"
#include "ADC.h"
#include "derivative.h" /* include peripheral declarations */
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
* @brief    UART_Init - Initalize the UART2 to run at 9600 bauds assuming bus clock of 20Mhz
* @param    none
* @return   none
*
************************************************************************************************/  
void UART_Init()
{
	SIM_SCGC |=  SIM_SCGC_UART2_MASK;		/* Enable bus clock in UART2*/
	UART2_BDH = 0;							/* One stop bit*/
	UART2_BDL = 8;						/* Baud rate at 9600*/
	UART2_C1  = 0;							/* No parity enable,8 bit format*/
	UART2_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART2_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	UART2_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
}

/***********************************************************************************************
*
* @brief    UART_SendChar - Send a single byte on UART2
* @param    byte to send
* @return   none
*
************************************************************************************************/  
void UART_SendChar(uint8_t send)
{
	while((UART2_S1 & UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
	(void)UART2_S1;								/* Read UART2_S1 register*/
	UART2_D=send;								/* Send data*/
}

/***********************************************************************************************
*
* @brief    UART_GetChar - Retrieve the received char from the UART2 buffer (should be called from Interrupt)
* @param    none
* @return   received byte
*
************************************************************************************************/  
uint8_t UART_GetChar()
{
	
	uint8_t recieve;
	while(( UART2_S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/
	(void) UART2_S1;								/* Read UART2_S1 register*/
	recieve= UART2_D;								/* Read received data*/
	return recieve;

} 

/***********************************************************************************************
*
* @brief    UART_SendStr - Print the String on Terminal Window
* @param    String to be sent
* @return   none
*
************************************************************************************************/
void UART_SendStr(char data_string[])
{
	int i=0;

	while(data_string[i] != '\0' || data_string[i]=='\n' || data_string[i]=='\r')
	{
		UART_SendChar(data_string[i]);
		i++;
	}
}

/***********************************************************************************************
*
* @brief    itoa - Converts integer to char
* @param    String to be sent
* @return   none
*
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.
	 * Downloaded from strudel.org.uk/itoa
***********************************************************************************************/

char* itoa_(int value, char* result, int base)
	{
		// check that the base is valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}
