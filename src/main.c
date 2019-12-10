/********************************************************************************
*    Single motor control                            							*
*    FRDM+KEA128 Board															*
*                                                                             	*
*    This code uses the UART module to communicate (two-way) with the Kinetic	*
*    board. A GUI built in Matlab will initiate connection and depending on the	*
*    commands being sent over UART will perform different actions such as moving
*    the motor a specific number of steps in a particular direction.			*
*    																			*    																			*
********************************************************************************/

/**********************************************************************************************
* External objects
**********************************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "UART.h"
#include "CLK.h"
#include "ADC.h"
#include "math.h"
#include "motorfuncs.h"
#include "GPIO.h"
#include "FTM.h"
#include "stdio.h"
#include "statisticsfunc.h"
#include "parsecommands.h"

//#include "string.h"
/**********************************************************************************************
* Global variables
**********************************************************************************************/

int InputVal=0;
int L_TapeMotion=20000;//in microns
int T_TapeMotion=2000;// in ms
int SeqA_ADC=1000;
int SeqC_ADC=3000;
int Calib1_ADC=2000;
int CalibSteps=10;
int SeqErrorCode=0;
int SequenceCount=1;

//Lock bits
int SeqALock=0;int SeqBLock=0;int SeqCLock=0;int SeqDLock=0;int SeqELock=0;int CalibMotorLock=0;
int SeqE_Lower=3000;int SeqE_Upper=4000;int SeqE_NSteps=4000;
int SeqInterrupt=0;
/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
//Initialize the motor variables
struct MotorVar MS1={0,1,0,7,0,1,1,0,21500,22000,1,0,1000,0,100,10,0};
struct MotorVar MS2={0,1,0,7,0,2,1,0,21500,22000,3,0,1000,0,100,10,0};
struct MotorVar MT1={0,1,0,7,0,3,1,0,24000,24000,2,0,1000,0,100,10,0};
struct MotorVar MT2={0,1,0,7,0,4,1,0,24000,24000,2,0,1000,0,100,10,0};
//Initialize tension variables
struct ADCTens T1={0,0,0,0,0,0,1,0,0,4000,10,ADC_CH0};
struct ADCTens T2={0,0,0,0,0,0,2,0,0,4000,10,ADC_CH1};
struct ADCTens T3={0,0,0,0,0,0,3,0,0,4000,10,ADC_CH2};


/**********************************************************************************************
* Local types
**********************************************************************************************/

char buffer[MAX_BUF];int sofar = 0;int parsedone=0;
int ADCCount=0;
/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/
void Enable_Interrupt(uint8_t vector_number);
void UART2_Interrupt();
void UART2_IRQHandler();
void FTM0_IRQHandler();void FTM0_Interrupt();
void FTM1_IRQHandler();void FTM1_Interrupt();
void FTM2_IRQHandler();void FTM2_Interrupt();

float ADCToVoltage(int val);
float VoltageToForce(double V);
int CheckTensionMeasurement();

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
* @brief    main() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
int main(void)
{
	/* Initialize Core Clock to 40MHz, Bus Clock to 20MHz  */
	Clk_Init();

	/* Configure button pins as inputs and LED pins as outputs */
	GPIO_Init();

	/*Initialize UART2 at 153600 bauds */
	UART_Init();

	/* Initialize the timers for MS1,MS2,MT1,MT2*/
	FTM_Init();

	/* Initialize the ADC module to read into T1,T2,T3 */
	ADC_InitALL();

	UART_SendStr("Waiting for commands.\n");
	Enable_Interrupt(UART2_IRQn);

	while(1);
	return 0;
}


/***********************************************************************************************
*
* @brief    Enable_Interrupt(uint8_t vector_number). Enable interrupts from desired module.
* @param    Module interrupt number from the interrupts vector table
* @return   none
*
************************************************************************************************/
void Enable_Interrupt(uint8_t vector_number)
{
	NVIC_ClearPendingIRQ(vector_number); 		/* Clear pending interrupt register */
	NVIC_EnableIRQ(vector_number); 				/* Enable required Interrupt */
	return;
}

void Disable_Interrupt(uint8_t vector_number)
{
	NVIC_ClearPendingIRQ(vector_number); 		/* Clear pending interrupt register */
	NVIC_DisableIRQ(vector_number); 				/* Disable required Interrupt */
	return;
}
/***********************************************************************************************
*
* @brief    UART2_Interrupt - Interrupt for UART
* @param    none
* @return   none
*
************************************************************************************************/

void UART2_Interrupt(void)
{
	//(void)UART2_S1;								/* Clear reception flag mechanism*/
	uint8_t send = UART_GetChar();				/* Get the Char */
	// Need this to reset the buffer and start gathering the new message.
	int NoCommandsParsed=0;
	if (parsedone)
	{
			sofar = 0;
			parsedone = 0;
	}

	if ((send=='\n') || (send=='\r') || (sofar==MAX_BUF))
	{
		buffer[sofar] = '\0';
		// Extract commands and other variables from this string
		NoCommandsParsed=sscanf(buffer,"%s %s %s %i \n \r",Command,TargetMotor,ExternObj,&InputVal);
		//parse_commands handles single motor instructions
		if(NoCommandsParsed==4)
		{
			parse_command(Command,TargetMotor,ExternObj,InputVal);
		}
		//parse_commandsSeq handles sequence motor instructions
		NoCommandsParsed=sscanf(buffer,"%s %s %i \n \r",Command,ExternObj,&InputVal);
		if(NoCommandsParsed==3)
		{
			parse_commandSeq(Command,ExternObj,InputVal);
		}
	}

	{
		buffer[sofar] = send;
		sofar++;
	}

}
/***********************************************************************************************
*
* @brief    UART2_IRQHandler - Interrupt for UART, Call user function.
* @param    none
* @return   none
*
************************************************************************************************/
void UART2_IRQHandler(void)
{
	UART2_Interrupt();
	return;
}
/***********************************************************************************************
*
* @brief    FTM0_IRQHandler - Interrupt for FTM0. This timer module moves MS1
* @param    none
* @return   none
*
************************************************************************************************/
void FTM0_IRQHandler()
{
	FTM0_Interrupt();
	return;
}
/***********************************************************************************************
*
* @brief    FTM1_IRQHandler - Interrupt for FTM1. This timer module moves MS2
* @param    none
* @return   none
*
************************************************************************************************/
void FTM1_IRQHandler()
{
	FTM1_Interrupt();
	return;
}
/***********************************************************************************************
*
* @brief    FTM1_IRQHandler - Interrupt for FTM2. This timer module moves MT1 and MT2
* @param    none
* @return   none
*
************************************************************************************************/
void FTM2_IRQHandler()
{
	FTM2_Interrupt();
	return;
}

/***********************************************************************************************
*
* @brief    FTM0_Interrupt() - User Function called by the FTM0 module on each timer interrupt.
* This timer periodically moves MS1
* @param    none
* @return   none
*
************************************************************************************************/
void FTM0_Interrupt()
{
	(void)FTM0_C0SC;  								/* Read to clear flag */
	FTM0_C0SC ^= FTM_CnSC_CHF_MASK;  				/* Clear flag */
	//Move motor match sequence
	if(MS1.MMMTSwitch==1 && MS1.MMMTLock==0)
	{
		Disable_Interrupt(FTM0_IRQn);
		MatchTension(&MS1);
		MS1.MMMTSwitch=0;
	}
	else
	{
		FTM0_SetPeriod(MS1.MotorSpeed);
		MoveMotor(&MS1);
		if(MS1.MotorConnected==0)
		{
			Disable_Interrupt(FTM0_IRQn);
		}
	}
	return;
}


/***********************************************************************************************
*
* @brief    FTM2_Interrupt() - User Function called by the FTM2 module on each timer interrupt.
* This timer periodically moves MS2
* @param    none
* @return   none
*
************************************************************************************************/
void FTM1_Interrupt()
{
	(void)FTM1_C1SC;  								/* Read to clear flag */
	FTM1_C1SC ^= FTM_CnSC_CHF_MASK;  				/* Clear flag */
	if(MS2.MMMTSwitch==1 && MS2.MMMTLock==0)
	{
		Disable_Interrupt(FTM1_IRQn);
		MatchTension(&MS2);
		MS2.MMMTSwitch=0;
	}
	else
	{
		FTM1_SetPeriod(MS2.MotorSpeed);
		MoveMotor(&MS2);
		if(MS2.MotorConnected==0)
		{
			Disable_Interrupt(FTM1_IRQn);
		}
	}
	return;
}


/***********************************************************************************************
*
* @brief    FTM2_Interrupt() - User Function called by the FTM2 module on each timer interrupt.
* This time moves MT1 and MT2 depending on whether the Motor Connected variable is set for MT1.
* @param    none
* @return   none
*
************************************************************************************************/
void FTM2_Interrupt()
{
	(void)FTM2_C2SC;  								/* Read to clear flag */
	FTM2_C2SC ^= FTM_CnSC_CHF_MASK;  				/* Clear flag */
	//MT1 and MT2 share the same interrupt and so switch between pulsing both motors via the MTX.MotorConnected option
	if(MT2.MMMTSwitch==1 && MT2.MMMTLock==0)
	{
		Disable_Interrupt(FTM2_IRQn);
		MatchTension(&MT2);
		MT2.MMMTSwitch=0;
	}
	else
	{
		if(MT1.MotorConnected==1 && MT2.MotorConnected==0)
		{
			FTM2_SetPeriod(MT1.MotorSpeed);
			MoveMotor(&MT1);
		}
		if(MT1.MotorConnected==0 && MT2.MotorConnected==1)
		{
			FTM2_SetPeriod(MT2.MotorSpeed);
			MoveMotor(&MT2);
		}
		if(MT1.MotorConnected==1 && MT2.MotorConnected==1)
		{
			FTM2_SetPeriod(MT1.MotorSpeed);
			MoveMotor(&MT1);
			MoveMotor(&MT2);
		}
		if(MT1.MotorConnected==0 && MT2.MotorConnected==0)
		{
			Disable_Interrupt(FTM2_IRQn);
		}
	}
	return;
}
/***********************************************************************************************
*
* @brief    CheckAllTension() - Command to check all tension measurements
* @param    none
* @return   val (1,0) if val is 0 tension has gone beyond limits!
*
************************************************************************************************/

int CheckTensionMeasurement()
{
	int val=1;
	T1.adc_currval=ADC_Read(ADC_CH1);	T2.adc_currval=ADC_Read(ADC_CH2);	T3.adc_currval=ADC_Read(ADC_CH3);
	//Check bounds
	if(T1.adc_currval<T1.adc_lowerval ||T1.adc_currval>T1.adc_upperval)
	{
		val=0;
	}
	if(T2.adc_currval<T2.adc_lowerval ||T2.adc_currval>T3.adc_upperval)
	{
		val=0;
	}
	if(T3.adc_currval<T3.adc_lowerval ||T3.adc_currval>T3.adc_upperval)
	{
		val=0;
	}
	return val;
}

/***********************************************************************************************
*
* @brief    ADCToVoltage() - Command to check all tension measurements
* @param    none
* @return   none
*
************************************************************************************************/
float ADCToVoltage(int val)
{
	return 0.0;
}
/***********************************************************************************************
*
* @brief    VoltageToForce() - Calculate force on tension arm via the ADC tension measurement.
* @param    none
* @return   none
*
************************************************************************************************/

float VoltageToForce(double V)
{
	return 0.0;
}

