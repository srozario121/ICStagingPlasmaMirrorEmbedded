/*
 * motorfuncs.c
 *
 *  Created on: 20 Oct 2017
 *      Author: svr11
 */




#include "motorfuncs.h"
#include "GPIO.h"

							/*****Set Motor Variable functions*****/
/***********************************************************************************************
*
* @brief    SetMotorDir() - Sets the direction variable for motor MX
* @param    none
* @return   none
*
************************************************************************************************/

void SetMotorDir(MotorVar *MX,int val)
{
		MX->DirVal=val;
	return;
}
/***********************************************************************************************
 *
* @brief    SetMotorSteps() - Sets the number of steps variable for motor MX
* @param    none
* @return   none
*
************************************************************************************************/

void SetMotorSteps(MotorVar *MX,int val)
{
	MX->NoStepsCurr=val;
	return;
}
/***********************************************************************************************
*
* @brief    SetMotorSpeed() - Sets the speed [10steps/s] variable for motor MX
* @param    none
* @return   none
*
************************************************************************************************/

void SetMotorSpeed(MotorVar *MX,uint32_t val)
{
	MX->MotorSpeed=val;
	if(MX->MotorNumber==1)
	{
		FTM0_SetPeriod(val);
	}
	else if(MX->MotorNumber==2)
	{
		FTM1_SetPeriod(val);
	}
	else if(MX->MotorNumber==3)
	{
		FTM2_SetPeriod(val);
	}
	else if(MX->MotorNumber==4)
	{
		FTM2_SetPeriod(val);
	}
	return;
}
/***********************************************************************************************
*
* @brief    StartMotorInterrupt(MotorVar *MX) - Starts the FTM timer interrupt for the relevant motor MX
* @param    none
* @return   none
*
************************************************************************************************/

void StartMotorInterrupt(MotorVar *MX)
{
	MX->MotorConnected=1;
	if(MX->MotorNumber==1)
	{
		Enable_Interrupt(FTM0_IRQn);
	}
	else if(MX->MotorNumber==2)
	{
		Enable_Interrupt(FTM1_IRQn);
	}
	else if(MX->MotorNumber==3)
	{
		Enable_Interrupt(FTM2_IRQn);
	}
	else if(MX->MotorNumber==4)
	{
		Enable_Interrupt(FTM2_IRQn);
	}
	return;
}
/***********************************************************************************************
*
* @brief    StopMotorInterrupt(MotorVar *MX) - Stops the FTM timer interrupt for the relevant motor MX
* @param    none
* @return   none
*
************************************************************************************************/

void StopMotorInterrupt(MotorVar *MX)
{
	MX->MotorConnected=0;
	if(MX->MotorNumber==1)
	{
		Disable_Interrupt(FTM0_IRQn);
	}
	else if(MX->MotorNumber==2)
	{
	Disable_Interrupt(FTM1_IRQn);
	}
	else if(MX->MotorNumber==3)
	{
	Disable_Interrupt(FTM2_IRQn);
	}
	else if(MX->MotorNumber==4)
	{
	Disable_Interrupt(FTM2_IRQn);
	}
	return;
}
/***********************************************************************************************
*
* @brief    ToggleMotor(MotorVar *MX,int Val) - Toggles the GPIO pins of a motor
* @param    none
* @return   none
*
************************************************************************************************/

void ToggleMotor(MotorVar *MX,int Val)
{

	if(MX->MotorNumber==1)
	{
		MS1STEP_TOGGLE;
	}
	else if(MX->MotorNumber==2)
	{
		MS2STEP_TOGGLE;
	}
	else if(MX->MotorNumber==3)
	{
		MT1STEP_TOGGLE;
	}
	else if(MX->MotorNumber==4)
	{
		MT2STEP_TOGGLE;
	}
		return;
}
/***********************************************************************************************
*
* @brief    MotorOff(MotorVar *MX) - Turns the step pin for all motors off
* @param    none
* @return   none
*
************************************************************************************************/

void MotorsOff(MotorVar *MX)
{
	if(MX->MotorNumber==1)
	{
		MS1STEP_OFF;
	}
	else if(MX->MotorNumber==2)
	{
		MS2STEP_OFF;
	}
	else if(MX->MotorNumber==3)
	{
		MT1STEP_OFF;
	}
	else if(MX->MotorNumber==4)
	{
		MT2STEP_OFF;
	}
		return;
}

void AllMotorsOff()
{
	MotorsOff(&MS1);	MotorsOff(&MS2);	MotorsOff(&MT1);	MotorsOff(&MT2);

}
/***********************************************************************************************
*
* @brief    MotorSequenceInterrupt{} - Sets the SeqInterrupt variable to 1 and cause all while loops
* in motor sequence functions to exit. Quick stop for all motors.
* @param    none
* @return   none
*
************************************************************************************************/

void MotorSequenceInterrupt()
{
	SeqInterrupt=1;

	StopMotorInterrupt(&MS1);StopMotorInterrupt(&MS2);
	StopMotorInterrupt(&MT1);StopMotorInterrupt(&MT2);
	MS1.MotorConnected=0;MS2.MotorConnected=0;
	MT1.MotorConnected=0;MT2.MotorConnected=0;

}
										/*****Sequence Motion functions*****/

/***********************************************************************************************
*
* @brief    MoveMotor() - Command to step the motor when interrupt is executed
* @param    none
* @return   none
*
************************************************************************************************/
void MoveMotor(MotorVar *MX)
{

	if(MX->NoStepsLeft>0)
	{ //If no steps is greater than 0 then enter stepping loop
		if(MX->DirVal==0)
		{// Change of direction by setting MXDIR_OFF/ON
			MX->AbsoluteSteps++;
			if(MX->MotorNumber==1)
			{
				MS1STEP_TOGGLE;MS1DIR_OFF;
				MX->NoStepsLeft--;

			}
			else if(MX->MotorNumber==2)
			{
				MS2STEP_TOGGLE;MS2DIR_OFF;
				MX->NoStepsLeft--;
			}
			else if(MX->MotorNumber==3)
			{
				MT1STEP_TOGGLE;MT1DIR_OFF;MT1COMM_ON;
				MX->NoStepsLeft--;
			}
			else if(MX->MotorNumber==4)
			{
				MT1STEP_TOGGLE;MT2DIR_OFF;MT2COMM_ON;
				MX->NoStepsLeft--;
			}
		}
		else if(MX->DirVal==1)
		{
			MX->AbsoluteSteps--;
			if(MX->MotorNumber==1)
			{
				MS1STEP_TOGGLE;MS1DIR_ON;
				MX->NoStepsLeft--;
			}

			if(MX->MotorNumber==2)
			{
				MS2STEP_TOGGLE;MS2DIR_ON;
				MX->NoStepsLeft--;
			}

			if(MX->MotorNumber==3)
			{
				MT1STEP_TOGGLE;MT1DIR_ON;MT1COMM_ON;
				MX->NoStepsLeft--;
			}

			if(MX->MotorNumber==4)
			{
				MT1STEP_TOGGLE;MT2DIR_ON;MT2COMM_ON;
				MX->NoStepsLeft--;
			}
		}
	}
	//When the number of steps have been stepped through turn interrupt off
	else
	{
		if (MX->MotorNumber==1)
		{
			Disable_Interrupt(FTM0_IRQn);
			MS1STEP_OFF;
		}

		if(MX->MotorNumber==2)
		{
			Disable_Interrupt(FTM1_IRQn);
			MS2STEP_OFF;
		}
		// As MT1 and MT2 share the same timer need to check that MT2 isnt connected when turning off the timer
		if(MX->MotorNumber==3 && MT2.MotorConnected==0)
		{
			Disable_Interrupt(FTM2_IRQn);
			MT1STEP_OFF;MT1COMM_OFF;MT2COMM_OFF;
		}
		if(MX->MotorNumber==3 && MT2.MotorConnected==1)
		{
			if(MT2.NoStepsLeft==0)
			{
			Disable_Interrupt(FTM2_IRQn);
			MT1STEP_OFF;MT1COMM_OFF;MT2COMM_OFF;
			}
			MT1COMM_OFF;
		}
		if(MX->MotorNumber==4 && MT1.MotorConnected==0)
		{
			Disable_Interrupt(FTM2_IRQn);
			MT1STEP_OFF;MT1COMM_OFF;MT2COMM_OFF;
		}
		if(MX->MotorNumber==4 && MT1.MotorConnected==1)
		{
			if(MT1.NoStepsLeft==0)
			{
			Disable_Interrupt(FTM2_IRQn);
			MT1STEP_OFF;MT1COMM_OFF;MT2COMM_OFF;
			}
			MT2COMM_OFF;
		}


	}
	return;
}


/***********************************************************************************************
*
* @brief    MoveMotorSeq() - Command to move the motors in sequence to spool tape
* @param    none
* @return   none
*
************************************************************************************************/

void MoveMotorSeq()
{
	CalibrateMotors();
	SeqDLock=1;
	//Motor sequences
	MotorSeqA();
	MotorSeqB();
	MotorSeqC();

	SeqDLock=0;
	return;
}
/***********************************************************************************************
*
* @brief    MoveMotorSeqPM1() - Command to move the spooler motors for PM in sequence to spool tape
* @param    none
* @return   none
*
************************************************************************************************/

void MoveMotorSeqPM1()
{
	SeqELock=1;
	int initialStep=0;
	//Move spooler A by a set number of steps
	initialStep=MS1.AbsoluteSteps;
	do{
	MoveMotorMatchTension(&MS1,0,&T1,SeqE_Lower);
	MoveMotorMatchTension(&MS2,1,&T2,SeqE_Upper);
	} while(abs(initialStep-SeqE_NSteps)<100);
	SeqELock=0;
	return;
}
/***********************************************************************************************
*
* @brief    MotorSeqA() - Command to move the motors in sequence to spool tape
* Sequence A is intended to equalize tension in all parts of the tape drive.
* @param    none
* @return   none
*
************************************************************************************************/

void MotorSeqA()
{
	if(SeqBLock==0 && SeqCLock==0  && CalibMotorLock==0)
	{
		//Block MotorSeqA being executed again until it has finished executing
		SeqALock=1;
		/*****Move MS1 clockwise till T1->SeqA_ADC*****/
		//Set motor direction to clockwise
		//Move motor to match tension
		MoveMotorMatchTension(&MS1,0,&T1,SeqA_ADC);

		/******Move MT2 counter clockwise till T2->SeqA_ADC*****/
		//Set motor direction to clockwise
		//Move motor to match tension
		MoveMotorMatchTension(&MT2,0,&T2,SeqA_ADC);

		/******Move MS2 counter clockwise till T3->SeqA_ADC******/
		//Move motor to match tension
		MoveMotorMatchTension(&MS2,0,&T3,SeqA_ADC);

		SeqALock=0;
	}
	return;
}
/***********************************************************************************************
*
* @brief    MotorSeqB() - Command to move the motors in sequence to spool tape
* Sequence B is intended to spool the tape at a constant speed by moving the motors by a different amount
* @param    none
* @return   none
*
************************************************************************************************/

void MotorSeqB()
{
	if(SeqALock==0 && SeqCLock==0  && CalibMotorLock==0)
	{
		SeqBLock=1;
		//Set MS1 parameters
		int Temp;
		Temp=TimeOfSequenceToMotorPeriod(&MS1)/10;
		SetMotorSteps(&MS1,LengthToSteps(&MS1));
		SetMotorSpeed(&MS1,Temp);
		SetMotorDir(&MS1,0);
		//Set MS1 parameters
		SetMotorSteps(&MS2,LengthToSteps(&MS2));
		SetMotorSpeed(&MS2,TimeOfSequenceToMotorPeriod(&MS2)/10);
		SetMotorDir(&MS2,0);
		//Set MS1 parameters
		SetMotorSteps(&MT1,LengthToSteps(&MT1));
		SetMotorSpeed(&MT1,TimeOfSequenceToMotorPeriod(&MT1)/10);
		SetMotorDir(&MT1,0);
		//Set MS1 parameters
		SetMotorSteps(&MT2,LengthToSteps(&MT2));
		SetMotorSpeed(&MT2,TimeOfSequenceToMotorPeriod(&MT2)/10);
		SetMotorDir(&MT2,0);

		//Start motor interrupts
		StartMotorInterrupt(&MS1);
		StartMotorInterrupt(&MS2);
		MT2.MotorConnected=1;//MT2 shares the same timer! So set it to go aswell
		StartMotorInterrupt(&MT1);
		//While all motors are connected and independently moving check tension!
		do
		{
			if(CheckTensionMeasurement()==0)
			{
				//Disconnect all motors
				MS1.MotorConnected=0;MS2.MotorConnected=0;
				MT1.MotorConnected=0;MT2.MotorConnected=0;
				//Disable all interrupts
				StopMotorInterrupt(&MS1);StopMotorInterrupt(&MS2);
				StopMotorInterrupt(&MT1);StopMotorInterrupt(&MT2);
			}
		}while(MS1.MotorConnected==1||MS2.MotorConnected==1||MT1.MotorConnected==1||MT2.MotorConnected==1);

		SeqBLock=1;
	}
	return;
}
/***********************************************************************************************
*
* @brief    MotorSeqC() - Command to arm the tractors to a higher tension
* Sequence C is intended to stretch the tape to flatten the surface.
* @param    none
* @return   none
*
************************************************************************************************/

void MotorSeqC()
{
	if(SeqALock==0 && SeqBLock==0 && CalibMotorLock==0)
	{
		//Move MS1 clockwise till T1->SeqA_T
		//Set motor direction to clockwise
		SeqCLock=1;
		//Move motor to match tension
		MoveMotorMatchTension(&MT1,0,&T1,SeqC_ADC);
		SeqCLock=1;
return;
	}
}
/***********************************************************************************************
*
* @brief    MoveMotorMatchTension() - Command move motor to match the tension measurement from the ADC
* @param    none
* @return   none
*
************************************************************************************************/
void MoveMotorMatchTension(MotorVar *MX,ADCTens *TX)
{
	MatchTensionStepCounter=0;
	//Set Motor Steps, Speed and direction
	SetMotorSteps(MX,10);		SetMotorSpeed(MX,500);
	MX->MotorConnected=1;
	LED0_OFF;
	//Move steps until adc value is close to the target adc value
	MX->MMMTSequenceSteps=0;
	do
	{
		//If no steps current is at 0 move motors
		if(MX->NoStepsCurr==0)
		{

			TX->adc_currval=ADC_Read(TX->ADC_ch);
			if(abs(TX->adc_currval-MX->MMMTADC)<MX->MMMTTol)
			{
				SetMotorDir(MX,MX->MMMTDirec);
			}
			else
			{
				SetMotorDir(MX,(int)(!(MX->MMMTDirec)));
			}
			MoveMotor(MX);
			MX->MMMTSequenceSteps=MX->MMMTSequenceSteps+10;
		}
		//If Target ADC and current adc are less that 10 counts away
		if(abs(TX->adc_currval-MX->MMMTADC)<MX->MMMTTol)
		{
			MX->MotorConnected=0;
		}

		//If stuck in an infinite loop or tension goes out of bound
		if(MX->MMMTSequenceSteps>MX->MMMTMaxLoopCounter || CheckTensionMeasurement()==0||SeqInterrupt==1)
		{
			//Release interrupt and lock bits
			SeqInterrupt=0;SeqErrorCode=1;
			SeqALock=0;SeqBLock=0;SeqCLock=0;SeqDLock=0;MatchTensionLock=0;
			MX->MotorConnected=0;MX->NoStepsCurr=0;
			break;
		}
		LED1_ON;
	}while((MX->MotorConnected==1) & (abs(TX->adc_currval-MX->MMMTADC)>10));
	LED1_OFF;
	return;

}

/***********************************************************************************************
*
* @brief    MatchTension() - Command move motor to match the tension measurement from the ADC
* @param    none
* @return   none
*
************************************************************************************************/
void MatchTension(MotorVar *MX)
{
	MX->MMMTLock=1;
		if(MatchTensionID==1)
		{
			LED0_ON;

			MoveMotorMatchTension(MX, &T1);

			LED2_ON;
		}
		else if(MatchTensionID==2)
		{
			MoveMotorMatchTension(MX, &T2);
		}
		else if(MatchTensionID==3)
		{
			MoveMotorMatchTension(MX, &T3);
		}
	MX->MMMTLock=0;
	return;
}
/***********************************************************************************************
*
* @brief    CalibrateMotors() - Command to move the motors in sequence to spool tape
* @param    none
* @return   none
*
************************************************************************************************/


void CalibrateMotors()
{
	CalibMotorLock=1;

	CalbrateStepMS1();
	CalbrateStepMS2();

	CalibMotorLock=0;
	return;
}
/***********************************************************************************************
*
* @brief    CalbrateStepMS1() - Function performs steps to figure out the radius of MS1
* @param    none
* @return   none
*
************************************************************************************************/

void CalbrateStepMS1()
{
	int Calib1CLoopCounter;
	int MS1_IntialStep,MT1_IntialStep;
	//Measure T1
	//Move MS1 until T1->Calib1_ADC
	T1.adc_intialval=ADC_Read(T1.ADC_ch);
	MS1_IntialStep=MS1.AbsoluteSteps;MT1_IntialStep=MT1.AbsoluteSteps;
	SetMotorSteps(&MS1,CalibSteps);		SetMotorSpeed(&MS1,100); SetMotorDir(&MS1,1);
	SetMotorSteps(&MT1,1);		SetMotorSpeed(&MT1,100);

	//Move motor 10 steps
	MoveMotor(&MS1);

	//Move MT2 until T1->Calib1_ADC
	Calib1CLoopCounter=0;//Initialise step counter
	do
	{
		//If no steps current is at 0 move motors
		if(MT1.NoStepsCurr==0)
		{
			MoveMotor(&MT1);Calib1CLoopCounter++;
			T1.adc_currval=ADC_Read(T1.ADC_ch);
		}
		//If Target ADC and current adc are less that 10 counts away
		if(abs(T1.adc_currval-T1.adc_intialval)<10)
		{
			MT1.MotorConnected=0;
		}
		Calib1CLoopCounter++;
		//If stuck in an infinite loop or tension goes out of bound
		if(Calib1CLoopCounter>100000 || CheckTensionMeasurement()==0||SeqInterrupt==1)
		{
			//Release interrupt and lock bits
			SeqInterrupt=0;
			SeqALock=0;SeqBLock=0;SeqCLock=0;SeqDLock=0;
			break;
		}
	}while((MT1.MotorConnected==1 &abs(T1.adc_currval-T1.adc_intialval)>10));
	//Calib1CLoopCounter is 2* the number of steps needed-> Radius of MS1=(Calib1CLoopCounter/2)*R_MT1/CalibSteps
	MS1.R0=(int)(MT1.R0*(Calib1CLoopCounter/2)/CalibSteps);
	//Undo steps
	SetMotorSteps(&MT1,abs(MT1_IntialStep-MT1.AbsoluteSteps));SetMotorDir(&MT1,0);
	MoveMotor(&MT1);
	SetMotorSteps(&MS1,abs(MS1_IntialStep-MS1.AbsoluteSteps));SetMotorDir(&MT1,0);
	MoveMotor(&MS1);
	return;
}
/***********************************************************************************************
*
* @brief    CalbrateStepMS2() - Function performs steps to figure out the radius of MS2
* @param    none
* @return   none
*
************************************************************************************************/

void CalbrateStepMS2()
{
	int Calib1CLoopCounter;
	int MS2_IntialStep,MT2_IntialStep;
	//Measure T1
	//Move MS1 until T1->Calib1_ADC
	T3.adc_intialval=ADC_Read(T3.ADC_ch);
	MS2_IntialStep=MS2.AbsoluteSteps;MT2_IntialStep=MT2.AbsoluteSteps;
	SetMotorSteps(&MS2,CalibSteps);		SetMotorSpeed(&MS2,100);
	SetMotorSteps(&MT2,1);		SetMotorSpeed(&MT2,100);

	//Move motor 10 steps
	MoveMotor(&MS2);

	//Move MT2 until T1->Calib1_ADC
	Calib1CLoopCounter=0;//Initialise step counter
	do
	{
		//If no steps current is at 0 move motors
		if(MT2.NoStepsCurr==0)
		{
			MoveMotor(&MT2);Calib1CLoopCounter++;
			T3.adc_currval=ADC_Read(T3.ADC_ch);
		}
		//If Target ADC and current adc are less that 10 counts away
		if(abs(T3.adc_currval-T3.adc_intialval)<10)
		{
			MT2.MotorConnected=0;
		}
		Calib1CLoopCounter++;
		//If stuck in an infinite loop or tension goes out of bound
		if(Calib1CLoopCounter>100000 || CheckTensionMeasurement()==0||SeqInterrupt==1)
		{
			//Release interrupt and lock bits
			SeqInterrupt=0;
			SeqALock=0;SeqBLock=0;SeqCLock=0;SeqDLock=0;
			break;
		}
	}while(MT2.MotorConnected==1 && (abs(T3.adc_currval-T3.adc_intialval)>10));
	//Calib1CLoopCounter is 2* the number of steps needed-> Radius of MS1=(Calib1CLoopCounter/2)*R_MT1/CalibSteps
	MS2.R0=(int)(MT2.R0*(Calib1CLoopCounter/2)/CalibSteps);

	//Undo steps
	SetMotorSteps(&MT1,abs(MT2_IntialStep-MT2.AbsoluteSteps));SetMotorDir(&MT1,0);
	MoveMotor(&MT1);
	SetMotorSteps(&MS1,abs(MS2_IntialStep-MS2.AbsoluteSteps));SetMotorDir(&MT1,0);
	MoveMotor(&MS1);
	return;
}

/*Steps/Periodicity calculation functions*/

/***********************************************************************************************
*
* @brief    LengthToSteps(MotorVar *MX) - Converts the length that the motor needs to travel
* based on the outer radius of each motor into steps
* @param    none
* @return   none
*
************************************************************************************************/

int LengthToSteps(MotorVar *MX)
{
	int result;
	result=(int)(L_TapeMotion/(2*3.141*MX->R0/2000));
	return result;
}
/***********************************************************************************************
*
* @brief    TimeOfSequenceToMotorPeriod(MotorVar *MX) - Converts the time required to move the motor
* by the appropriate length into a time and calculates the speed that the motor needs to move.
* @param    none
* @return   none
*
************************************************************************************************/

int TimeOfSequenceToMotorPeriod(MotorVar *MX)
{
	int result;
	result=(int)(T_TapeMotion/LengthToSteps(MX));
	return result;
}
