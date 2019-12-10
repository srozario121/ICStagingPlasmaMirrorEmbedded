/*
 * parsecommands.c
 *
 *  Created on: 22 Oct 2017
 *      Author: svr11
 */

#include "parsecommands.h"


/***********************************************************************************************
* @brief    parse_command- Parses instructions for single motor movement/single adc read events
* @param    none
* @return   none
*
************************************************************************************************/

void parse_command(char Command[MAX_BUF],char TargetMotor[MAX_BUF], char ExternObj[MAX_BUF],int Val)
{
    int CommandSuccessful=0;
    char str[MAX_BUF];char str1[MAX_BUF];char str2[MAX_BUF];char str3[MAX_BUF];
    								/* Move commands*/
    if(strcmp(Command,"Move")==0)
    {
        if(strcmp(ExternObj,"Motor")==0)
        {
        	// Command to move just motor MS1
        	if(strcmp(TargetMotor,"MSA")==0)
        	{

				if (Val==1) // Move motor
				{
					if(MS1.MotorConnected==1) //Check that motor is connected
					{
						MS1DISABLE_OFF;
						MS1.NoStepsLeft=MS1.NoStepsCurr;
						Enable_Interrupt(FTM0_IRQn);
						CommandSuccessful=1;

						UART_SendStr("Command parsed. Moving motor \n \r");
					}
					else if(MS1.MotorConnected==0)
					{

						CommandSuccessful=1;
						sprintf(str,"Command parsed but motor is unconnected: %i \n \r",MS1.MotorConnected);
						UART_SendStr(str);
					}
				}
				if (Val==0) //Stop moving motor
				{
					MS1DISABLE_ON;
					Disable_Interrupt(FTM0_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping motor \n \r");
				}
        	}

        	// Command to move just motor MS2
        	else if(strcmp(TargetMotor,"MSB")==0)
			{
				if (Val==1) // Move motor
				{
					if(MS2.MotorConnected==1) //Check that motor is connected
					{
						MS2DISABLE_OFF;
						MS2.NoStepsLeft=MS2.NoStepsCurr;
						Enable_Interrupt(FTM1_IRQn);
						CommandSuccessful=1;

						UART_SendStr("Command parsed. Moving motor \n \r");
					}
					else if(MS2.MotorConnected==0)	//Give warning when motor is unconnected
					{
						CommandSuccessful=1;
						sprintf(str,"Command parsed but motor is unconnected: %i \n \r",MS2.MotorConnected);
						UART_SendStr(str);
					}
				}
				if (Val==0) //Stop moving motor
				{
					MS2DISABLE_ON;
					Disable_Interrupt(FTM1_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping motor \n \r");
				}
			}
				// Command to move just motor MT1
        	else if(strcmp(TargetMotor,"MTA")==0)
			{
				if (Val==1) // Move motor
				{
					if(MT1.MotorConnected==1) //Check that motor is connected
					{
						MT1DISABLE_OFF;
						MT1.NoStepsLeft=MT1.NoStepsCurr;
						Enable_Interrupt(FTM2_IRQn);
						CommandSuccessful=1;
						UART_SendStr("Command parsed. Moving motor \n \r");
					}
					else if(MT1.MotorConnected==0)	//Give warning when motor is unconnected
					{
						CommandSuccessful=1;
						sprintf(str,"Command parsed but motor is unconnected: %i \n \r",MT1.MotorConnected);
						UART_SendStr(str);
					}
				}
				if (Val==0) //Stop moving motor
				{
					MT1DISABLE_ON;
					Disable_Interrupt(FTM2_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping motor \n \r");
				}
			}
				// Command to move just motor MT2
        	else if(strcmp(TargetMotor,"MTB")==0)
			{
				if (Val==1) // Move motor
				{
					if(MT2.MotorConnected==1) //Check that motor is connected
					{
						MT2DISABLE_OFF;
						MT2.NoStepsLeft=MT2.NoStepsCurr;
						Enable_Interrupt(FTM2_IRQn);
						CommandSuccessful=1;
						UART_SendStr("Command parsed. Moving motor \n \r");
					}
					else if (MT2.MotorConnected==0)	//Give warning when motor is unconnected
					{
						CommandSuccessful=1;
						sprintf(str,"Command parsed but motor is unconnected: %i \n \r",MT2.MotorConnected);
						UART_SendStr(str);
					}
				}
				if (Val==0) //Stop moving motor
				{
					MT2DISABLE_ON;
					Disable_Interrupt(FTM2_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping motor \n \r");
				}
			}
        	else if(strcmp(TargetMotor,"MTC")==0)
			{
				if (Val==1) // Move motor
				{
					if(MT1.MotorConnected==1 & MT2.MotorConnected==1 ) //Check that motor is connected
					{
						MT1DISABLE_OFF;MT2DISABLE_OFF;
						MT2.NoStepsLeft=MT2.NoStepsCurr;
						MT1.NoStepsLeft=MT1.NoStepsCurr;

						Enable_Interrupt(FTM2_IRQn);
						CommandSuccessful=1;
						UART_SendStr("Command parsed. Moving motor \n \r");
					}
					else	//Give warning when motor is unconnected
					{
						CommandSuccessful=1;
						sprintf(str,"Command parsed but motor MT1 and 2 are unconnected: %i \n \r",MT2.MotorConnected);
						UART_SendStr(str);
					}
				}
				if (Val==0) //Stop moving motor
				{
					MT1DISABLE_ON;MT2DISABLE_ON;
					Disable_Interrupt(FTM2_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping motor \n \r");
				}
			}
        }
        else if(strcmp(ExternObj,"MT")==0)
        {
        	if(strcmp(TargetMotor,"MSA")==0)
			{
        		if(Val==1)// Need to check val to make sure number of steps is in bound
				{
        			//Set MSA MMT switch to 1
        			MS1.MMMTSwitch=1;
        			Enable_Interrupt(FTM0_IRQn);
        			CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Initiating MT for MSA \n \r");
				}
        		else if(Val==0)
        		{
        			MS1.MMMTSwitch=0;
					Disable_Interrupt(FTM0_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping MT for MSA \n \r");
        		}
			}
        	else if(strcmp(TargetMotor,"MSB")==0)
			{
        		if(Val==1)// Need to check val to make sure number of steps is in bound
				{
        			//Set MSA MMT switch to 1
        			MS2.MMMTSwitch=1;
        			Enable_Interrupt(FTM1_IRQn);
        			CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Initiating MT for MSB \n \r");
				}
        		else if(Val==0)
        		{
        			MS2.MMMTSwitch=0;
					Disable_Interrupt(FTM1_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping MT for MSB \n \r");
        		}
			}
        	else if(strcmp(TargetMotor,"MTB")==0)
			{
				if(Val==1)// Need to check val to make sure number of steps is in bound
				{
					//Set MSA MMT switch to 1
					MT2.MMMTSwitch=1;
					Enable_Interrupt(FTM2_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Initiating MT for MTB \n \r");
				}
				else if(Val==0)
				{
					MT2.MMMTSwitch=0;
					Disable_Interrupt(FTM2_IRQn);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Stopping MT for MTB \n \r");
				}
			}

		}
    }
    								/* Set commands*/
	else if(strcmp(Command,"Set")==0)
	{
		if(strcmp(ExternObj,"Steps")==0)
		{
			if(Val>0)// Need to check val to make sure number of steps is in bound
			{
				if(strcmp(TargetMotor,"MSA")==0)
				{
					SetMotorSteps(&MS1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Steps set for MS1 \n \r");
				}
				else if(strcmp(TargetMotor,"MSB")==0)
				{
					SetMotorSteps(&MS2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Steps set for MS2 \n \r");
				}
				else if(strcmp(TargetMotor,"MTA")==0)
				{
					SetMotorSteps(&MT1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Steps set for MT1 \n \r");
				}
				else if(strcmp(TargetMotor,"MTB")==0)
				{
					SetMotorSteps(&MT2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Steps set for MT2 \n \r");
				}
			}
			else
			{
				UART_SendStr("Command parsed but step val out of range \n \r");
			}
		}
		if(strcmp(ExternObj,"Dir")==0)
		{
			if(Val==0||Val==1)
			{
				if(strcmp(TargetMotor,"MSA")==0)
				{
					SetMotorDir(&MS1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Dir set for MS1 \n \r");
				}
				else if(strcmp(TargetMotor,"MSB")==0)
				{
					SetMotorDir(&MS2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Dir set for MS2 \n \r");
				}
				else if(strcmp(TargetMotor,"MTA")==0)
				{
					SetMotorDir(&MT1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Dir set for MT1 \n \r");
				}
				else if(strcmp(TargetMotor,"MTB")==0)
				{
					SetMotorDir(&MT2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Dir set for MT1 \n \r");
				}
			}
			else
			{
				CommandSuccessful=1;
				UART_SendStr("Command parsed but dir val out of range \n \r");
			}
		}
		if(strcmp(ExternObj,"Speed")==0)
		{
			if(Val>0|| Val<15625)
			{

				if(strcmp(TargetMotor,"MSA")==0)
				{
					SetMotorSpeed(&MS1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Speed set for MS1 \n \r");
				}
				else if(strcmp(TargetMotor,"MSB")==0)
				{
					SetMotorSpeed(&MS2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Speed set for MS1 \n \r");
				}
				else if(strcmp(TargetMotor,"MTA")==0)
				{
					SetMotorSpeed(&MT1,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Speed set for MS1 \n \r");
				}
				else if(strcmp(TargetMotor,"MTB")==0)
				{
					SetMotorSpeed(&MT2,Val);					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Speed set for MS1 \n \r");
				}
				else
				{
					CommandSuccessful=1;
					UART_SendStr("Command parsed but target motor arg is wrong \n \r");
				}
			}
			else
			{
				CommandSuccessful=1;
				UART_SendStr("Command parsed but speed arg is out of range \n \r");
			}
		}
		if(strcmp(ExternObj,"Prescaler")==0)
		{
			if(strcmp(TargetMotor,"MSA")==0)
			{
				if(Val>1|| Val<8)
				{
					MS1.PrescalerVal=Val;
					FTM0_SetPrescaler(MS1.PrescalerVal);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Prescaler set for MS1 \n \r");
				}
				else
				{
					CommandSuccessful=1;
					UART_SendStr("Command parsed but prescaler val out of range \n \r");
				}
			}
			else if(strcmp(TargetMotor,"MSB")==0)
			{
				if(Val>1|| Val<8)
				{
					MS2.PrescalerVal=Val;
					FTM1_SetPrescaler(MS2.PrescalerVal);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Prescaler set for MS2 \n \r");
				}
				else
				{
					CommandSuccessful=1;
					UART_SendStr("Command parsed but prescaler val out of range \n \r");
				}
			}
			else if(strcmp(TargetMotor,"MTA")==0)
			{
				if(Val>1|| Val<8)
				{
					MT1.PrescalerVal=Val;
					FTM2_SetPrescaler(MT1.PrescalerVal);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Prescaler set MT1 \n \r");
				}
				else
				{
					CommandSuccessful=1;
					UART_SendStr("Command parsed but prescaler val out of range \n \r");
				}
			}
			else if(strcmp(TargetMotor,"MTB")==0)
			{
				if(Val>1|| Val<8)
				{
					MT2.PrescalerVal=Val;
					FTM2_SetPrescaler(MT2.PrescalerVal);
					CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Prescaler set for MT2 \n \r");
				}
				else
				{
					CommandSuccessful=1;
					UART_SendStr("Command parsed but prescaler val out of range \n \r");
				}
			}
		}

		if(strcmp(ExternObj,"MConnect")==0)
		{
			if(strcmp(TargetMotor,"MSA")==0)
			{
				if(Val==1)
				{
					MS1.MotorConnected=1;
					UART_SendStr("Motor MS1 is connected \n \r");
					CommandSuccessful=1;
				}
				else if(Val==0)
				{

					MS1.MotorConnected=0;
					UART_SendStr("Motor MS1 is disconnected \n \r");
					CommandSuccessful=1;
				}
			}
			else if(strcmp(TargetMotor,"MSB")==0)
			{
				if(Val==1)
				{
					MS2.MotorConnected=1;
					UART_SendStr("Motor MS2 is connected \n \r");
					CommandSuccessful=1;
				}
				else if(Val==0)
				{

					MS2.MotorConnected=0;
					UART_SendStr("Motor MS2 is disconnected \n \r");
					CommandSuccessful=1;
				}
			}
			else if(strcmp(TargetMotor,"MTA")==0)
			{
				if(Val==1)
				{
					MT1.MotorConnected=1;
					UART_SendStr("Motor MT1 is connected \n \r");
					CommandSuccessful=1;
				}
				else if(Val==0)
				{

					MT1.MotorConnected=0;
					UART_SendStr("Motor MT1 is disconnected \n \r");
					CommandSuccessful=1;
				}
			}
			else if(strcmp(TargetMotor,"MTB")==0)
			{
				if(Val==1)
				{
					MT2.MotorConnected=1;
					UART_SendStr("Motor MT2 is connected \n \r");
					CommandSuccessful=1;
				}
				else if(Val==0)
				{

					MT2.MotorConnected=0;
					UART_SendStr("Motor MT2 is disconnected \n \r");
					CommandSuccessful=1;
				}
			}
		}//int MMMTSwitch;int MMMTMaxLoopCounter;int MMMTDirec;int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
		if(strcmp(ExternObj,"MTNo")==0)
		{
			if(strcmp(TargetMotor,"MSA")==0)
			{
					MS1.MMMT_TensionNo=Val;
					UART_SendStr("Motor MS1 MMMT_TNo is set \n \r");
					CommandSuccessful=1;
			}
			else if(strcmp(TargetMotor,"MSB")==0)
			{
					MS2.MMMT_TensionNo=Val;
					UART_SendStr("Motor MS2 MMMT_TNo is set \n \r");
					CommandSuccessful=1;

			}
			else if(strcmp(TargetMotor,"MTA")==0)
			{
					MT1.MMMT_TensionNo=Val;
					UART_SendStr("Motor MT1 MMMT_TNo is set \n \r");
					CommandSuccessful=1;
			}
			else if(strcmp(TargetMotor,"MTB")==0)
			{
					MT2.MMMT_TensionNo=Val;
					UART_SendStr("Motor MT2 MMMT_TNo is set \n \r");
					CommandSuccessful=1;
			}
		}
		//int MMMTMaxLoopCounter;int MMMTDirec;int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
				if(strcmp(ExternObj,"MMMTSwitch")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTSwitch=Val;
							UART_SendStr("Motor MS1 MMMTSwitch is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTSwitch=Val;
							UART_SendStr("Motor MS2 MMMTSwitch is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTSwitch=Val;
							UART_SendStr("Motor MT1 MMMTSwitch is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTSwitch=Val;
							UART_SendStr("Motor MT2 MMMTSwitch is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTDirec;int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
				if(strcmp(ExternObj,"MMMTMaxLoopCounter")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTMaxLoopCounter=Val;
							UART_SendStr("Motor MS1 MMMTMaxLoopCounter is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTMaxLoopCounter=Val;
							UART_SendStr("Motor MS2 MMMTMaxLoopCounter is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTMaxLoopCounter=Val;
							UART_SendStr("Motor MT1 MMMTMaxLoopCounter is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTMaxLoopCounter=Val;
							UART_SendStr("Motor MT2 MMMTMaxLoopCounter is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
				if(strcmp(ExternObj,"MMMTDirec")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTDirec=Val;
							UART_SendStr("Motor MS1 MMMTDirec is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTDirec=Val;
							UART_SendStr("Motor MS2 MMMTDirec is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTDirec=Val;
							UART_SendStr("Motor MT1 MMMTDirec is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTDirec=Val;
							UART_SendStr("Motor MT2 MMMTDirec is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
				if(strcmp(ExternObj,"MMMTADC")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTADC=Val;
							UART_SendStr("Motor MS1 MMMTADC is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTADC=Val;
							UART_SendStr("Motor MS2 MMMTADC is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTADC=Val;
							UART_SendStr("Motor MT1 MMMTADC is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTADC=Val;
							UART_SendStr("Motor MT2 MMMTADC is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTSequenceSteps;int MMMTLock;
				if(strcmp(ExternObj,"MMMTTol")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTTol=Val;
							UART_SendStr("Motor MS1 MMMTTol is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTTol=Val;
							UART_SendStr("Motor MS2 MMMTTol is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTTol=Val;
							UART_SendStr("Motor MT1 MMMTTol is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTTol=Val;
							UART_SendStr("Motor MT2 MMMTTol is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTLock;
				if(strcmp(ExternObj,"MMMTSequenceSteps")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTSequenceSteps=Val;
							UART_SendStr("Motor MS1 MMMTSequenceSteps is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTSequenceSteps=Val;
							UART_SendStr("Motor MS2 MMMTSequenceSteps is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTSequenceSteps=Val;
							UART_SendStr("Motor MT1 MMMTSequenceSteps is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTSequenceSteps=Val;
							UART_SendStr("Motor MT2 MMMTSequenceSteps is set \n \r");
							CommandSuccessful=1;
					}
				}
				//int MMMTLock;
				if(strcmp(ExternObj,"MMMTLock")==0)
				{
					if(strcmp(TargetMotor,"MSA")==0)
					{
							MS1.MMMTLock=Val;
							UART_SendStr("Motor MS1 MMMTLock is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MSB")==0)
					{
							MS2.MMMTLock=Val;
							UART_SendStr("Motor MS2 MMMTLock is set \n \r");
							CommandSuccessful=1;

					}
					else if(strcmp(TargetMotor,"MTA")==0)
					{
							MT1.MMMTLock=Val;
							UART_SendStr("Motor MT1 MMMTLock is set \n \r");
							CommandSuccessful=1;
					}
					else if(strcmp(TargetMotor,"MTB")==0)
					{
							MT2.MMMTLock=Val;
							UART_SendStr("Motor MT2 MMMTLock is set \n \r");
							CommandSuccessful=1;
					}
				}

    }
    							/* Get commands*/
	else if(strcmp(Command,"Get")==0)
	{
		if(strcmp(TargetMotor,"MSA")==0)
		{
			if(strcmp(ExternObj,"Steps")==0)
			{
				sprintf(str,"Motor MS1 steps left: %i \n \r",MS1.NoStepsLeft);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"StepsCurr")==0)
			{
				sprintf(str,"Motor MS1 steps set: %i \n \r",MS1.NoStepsCurr);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Dir")==0)
			{
				sprintf(str,"Motor MS1 direction is: %i \n \r",MS1.DirVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Speed")==0)
			{
				sprintf(str,"Motor MS1 speed is: %i \n \r",(int)MS1.MotorSpeed);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Prescaler")==0)
			{
				sprintf(str,"Motor MS1 prescaler is: %i \n \r",MS1.PrescalerVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}//MTNo
			else if(strcmp(ExternObj,"MConnect")==0)
			{
				sprintf(str,"Motor MS1 connection status is: %i \n \r",MS1.MotorConnected);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MTNo")==0)
			{
				sprintf(str,"Motor MS1 connection status is: %i \n \r",MS1.MMMT_TensionNo);
				UART_SendStr(str);
				CommandSuccessful=1;
			}//int MMMTMaxLoopCounter;int MMMTDirec;int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
			else if(strcmp(ExternObj,"MMMTSwitch")==0)
			{
				sprintf(str,"Motor MS1 MMMTSwitch : %i \n \r",MS1.MMMTSwitch);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			//int MMMTMaxLoopCounter;int MMMTDirec;int MMMTADC;int MMMTTol;int MMMTSequenceSteps;int MMMTLock;
			else if(strcmp(ExternObj,"MMMTMaxLoopCounter")==0)
			{
				sprintf(str,"Motor MS1 MMMTMaxLoopCounter : %i \n \r",MS1.MMMTMaxLoopCounter);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTDirec")==0)
			{
				sprintf(str,"Motor MS1 MMMTDirec : %i \n \r",MS1.MMMTDirec);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTADC")==0)
			{
				sprintf(str,"Motor MS1 MMMTADC : %i \n \r",MS1.MMMTADC);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTTol")==0)
			{
				sprintf(str,"Motor MS1 MMMTTol : %i \n \r",MS1.MMMTTol);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSequenceSteps")==0)
			{
				sprintf(str,"Motor MS1 MMMTSequenceSteps : %i \n \r",MS1.MMMTSequenceSteps);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTLock")==0)
			{
				sprintf(str,"Motor MS1 MMMTLock : %i \n \r",MS1.MMMTLock);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"MSB")==0)
		{
			if(strcmp(ExternObj,"Steps")==0)
			{
				sprintf(str,"Motor MS2 steps left: %i \n \r",MS2.NoStepsLeft);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"StepsCurr")==0)
			{
				sprintf(str,"Motor MS2 steps set: %i \n \r",MS2.NoStepsCurr);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Dir")==0)
			{
				sprintf(str,"Motor MS2 direction is: %i \n \r",MS2.DirVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Speed")==0)
			{
				sprintf(str,"Motor MS2 speed is: %i \n \r",(int)MS2.MotorSpeed);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Prescaler")==0)
			{
				sprintf(str,"Motor MS2 prescaler is: %i \n \r",MS2.PrescalerVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"MConnect")==0)
			{
				sprintf(str,"Motor MS2 connection status is: %i \n \r",MS2.MotorConnected);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MTNo")==0)
			{
				sprintf(str,"Motor MS2 MTNo : %i \n \r",MS2.MMMT_TensionNo);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSwitch")==0)
			{
				sprintf(str,"Motor MS2 MMMTSwitch : %i \n \r",MS2.MMMTSwitch);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTMaxLoopCounter")==0)
			{
				sprintf(str,"Motor MS2 MMMTMaxLoopCounter : %i \n \r",MS2.MMMTMaxLoopCounter);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTDirec")==0)
			{
				sprintf(str,"Motor MS2 MMMTDirec : %i \n \r",MS2.MMMTDirec);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTADC")==0)
			{
				sprintf(str,"Motor MS2 MMMTADC : %i \n \r",MS2.MMMTADC);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTTol")==0)
			{
				sprintf(str,"Motor MS2 MMMTTol : %i \n \r",MS2.MMMTTol);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSequenceSteps")==0)
			{
				sprintf(str,"Motor MS2 MMMTSequenceSteps : %i \n \r",MS2.MMMTSequenceSteps);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTLock")==0)
			{
				sprintf(str,"Motor MS2 MMMTLock : %i \n \r",MS2.MMMTLock);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"MTA")==0)
		{
			if(strcmp(ExternObj,"Steps")==0)
			{
				sprintf(str,"Motor MT1 steps left: %i \n \r",MT1.NoStepsLeft);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"StepsCurr")==0)
			{
				sprintf(str,"Motor MT1 steps set: %i \n \r",MT1.NoStepsCurr);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Dir")==0)
			{
				sprintf(str,"Motor MT1 direction is: %i \n \r",MT1.DirVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Speed")==0)
			{
				sprintf(str,"Motor MT1 speed is: %i \n \r",(int)MT1.MotorSpeed);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Prescaler")==0)
			{
				sprintf(str,"Motor MT1 prescaler is: %i \n \r",MT1.PrescalerVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"MConnect")==0)
			{
				sprintf(str,"Motor MT1 connection status is: %i \n \r",MT1.MotorConnected);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MTNo")==0)
			{
				sprintf(str,"Motor MT1 MTNo : %i \n \r",MT1.MMMT_TensionNo);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSwitch")==0)
			{
				sprintf(str,"Motor MT1 MMMTSwitch : %i \n \r",MT1.MMMTSwitch);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTMaxLoopCounter")==0)
			{
				sprintf(str,"Motor MT1 MMMTMaxLoopCounter : %i \n \r",MT1.MMMTMaxLoopCounter);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTDirec")==0)
			{
				sprintf(str,"Motor MT1 MMMTDirec : %i \n \r",MT1.MMMTDirec);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTADC")==0)
			{
				sprintf(str,"Motor MT1 MMMTADC : %i \n \r",MT1.MMMTADC);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTTol")==0)
			{
				sprintf(str,"Motor MT1 MMMTTol : %i \n \r",MT1.MMMTTol);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSequenceSteps")==0)
			{
				sprintf(str,"Motor MT1 MMMTSequenceSteps : %i \n \r",MT1.MMMTSequenceSteps);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTLock")==0)
			{
				sprintf(str,"Motor MT1 MMMTLock : %i \n \r",MT1.MMMTLock);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"MTB")==0)
		{
			if(strcmp(ExternObj,"Steps")==0)
			{
				sprintf(str,"Motor MT2 steps left: %i \n \r",MT2.NoStepsLeft);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"StepsCurr")==0)
			{
				sprintf(str,"Motor MT2 steps set: %i \n \r",MT2.NoStepsCurr);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Dir")==0)
			{
				sprintf(str,"Motor MT2 direction is: %i \n \r",MT2.DirVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Speed")==0)
			{
				sprintf(str,"Motor MT2 speed is: %i \n \r",(int)MT2.MotorSpeed);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"Prescaler")==0)
			{
				sprintf(str,"Motor MT2 prescaler is: %i \n \r",MT2.PrescalerVal);
				CommandSuccessful=1;
				UART_SendStr(str);
			}
			else if(strcmp(ExternObj,"MConnect")==0)
			{
				sprintf(str,"Motor MT2 connection status is: %i \n \r",MT2.MotorConnected);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MTNo")==0)
			{
				sprintf(str,"Motor MT2 MTNo : %i \n \r",MT2.MMMT_TensionNo);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSwitch")==0)
			{
				sprintf(str,"Motor MT2 MMMTSwitch : %i \n \r",MT2.MMMTSwitch);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTMaxLoopCounter")==0)
			{
				sprintf(str,"Motor MT2 MMMTMaxLoopCounter : %i \n \r",MT2.MMMTMaxLoopCounter);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTDirec")==0)
			{
				sprintf(str,"Motor MT2 MMMTDirec : %i \n \r", MT2.MMMTDirec);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTADC")==0)
			{
				sprintf(str,"Motor MT2 MMMTADC : %i \n \r",MT2.MMMTADC);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTTol")==0)
			{
				sprintf(str,"Motor MS2 MMMTTol : %i \n \r",MT2.MMMTTol);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTSequenceSteps")==0)
			{
				sprintf(str,"Motor MT2 MMMTSequenceSteps : %i \n \r",MT2.MMMTSequenceSteps);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
			else if(strcmp(ExternObj,"MMMTLock")==0)
			{
				sprintf(str,"Motor MT2 MMMTLock : %i \n \r",MT2.MMMTLock);
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}//MMMTSwitch

		// Get tension measurement
		if(strcmp(TargetMotor,"TA")==0)
		{
			if(strcmp(ExternObj,"Weight")==0)//This bit reads the ADC
			{
				adc_value=ADC_Read(ADC_CH0);
				itoa_((int)adc_value,str,10);					/*Convert integer to string*/
				strcat(str," is the current ADC value \n \r");		/*Concatenate strings*/
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"TB")==0)
		{
			if(strcmp(ExternObj,"Weight")==0)//This bit reads the ADC
			{
				adc_value=ADC_Read(ADC_CH1);
				itoa_((int)adc_value,str,10);					/*Convert integer to string*/
				strcat(str," is the current ADC value \n \r");		/*Concatenate strings*/
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"TC")==0)
		{
			if(strcmp(ExternObj,"Weight")==0)//This bit reads the ADC
			{
				adc_value=ADC_Read(ADC_CH2);
				itoa_((int)adc_value,str,10);					/*Convert integer to string*/
				strcat(str," is the current ADC value \n \r");		/*Concatenate strings*/
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
		else if(strcmp(TargetMotor,"TD")==0)
		{
			if(strcmp(ExternObj,"Weight")==0)//This bit reads the ADC
			{
				//Accumulate some ADC measurement
				int j=0;
				for(j=0;j<ARRAYLEN;j++)
				{
					T1Measure[j]=(int)(ADC_Read(ADC_CH0));T2Measure[j]=(int)(ADC_Read(ADC_CH1));T3Measure[j]=(int)(ADC_Read(ADC_CH2));
				}
				//Accumulate statistics from these measurements
				//int StdArray(int* InputArray)
				T1MeanValue=MeanArray(&T1Measure);T2MeanValue=MeanArray(&T2Measure);T3MeanValue=MeanArray(&T3Measure);
				T1StdValue=StdArray(&T1Measure);T2StdValue=StdArray(&T2Measure);T3StdValue=StdArray(&T3Measure);

				itoa_((int)T1MeanValue,str1,10);itoa_((int)T2MeanValue,str2,10);itoa_((int)T3MeanValue,str3,10);
//First three values are mean values, next three values are std deviation
				strcat(str,str1);
				strcat(str,",");
				strcat(str,str2);
				strcat(str,",");
				strcat(str,str3);
				strcat(str,",");

				itoa_((int)T1StdValue,str1,10);itoa_((int)T2StdValue,str2,10);itoa_((int)T3StdValue,str3,10);

				strcat(str,str1);
				strcat(str,",");
				strcat(str,str2);
				strcat(str,",");
				strcat(str,str3);
				strcat(str,",");

				strcat(str," ADCs \n \r");		/*Concatenate strings*/
				UART_SendStr(str);
				CommandSuccessful=1;
			}
		}
	}
    //Check if command was successful
    if(CommandSuccessful==0)
    {
    	UART_SendStr("Warning command was not parsed from GUI.\n \r");
    }
    parsedone=1;
    return;
}
/***********************************************************************************************
* @brief    parse_commandSeq- Parses instructions for sequence motor movement/single adc read events
* @param    none
* @return   none
*
************************************************************************************************/

void parse_commandSeq(char Command[MAX_BUF],char ExternObj[MAX_BUF],int Val)
{
    int CommandSuccessful=0;
    char str[MAX_BUF];char str1[MAX_BUF];char str2[MAX_BUF];char str3[MAX_BUF];
    //Command level
    if(strcmp(Command,"Move")==0)
    {
    	/*****Move Commands*****/
    	if(strcmp(ExternObj,"SeqA")==0)
    	{
    		if(SeqALock==0 && SeqBLock==0 && SeqCLock==0 && SeqDLock==0)
    		{
    			if(Val==1)
    			{
					MotorSeqA();
					CommandSuccessful=1;
					UART_SendStr("Command parsed. Sequence A initiated \n \r");
    			}
    			else if(Val==0)
    			{
    				MotorSequenceInterrupt();CommandSuccessful=1;
    				UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
    			}
    		}
    		else
    		{
    			CommandSuccessful=1;
				UART_SendStr("Warning: Sequence conflict occurring \n \r");
    		}

    	}
    	else if(strcmp(ExternObj,"SeqB")==0)
    	{
    		if(SeqALock==0 && SeqBLock==0 && SeqCLock==0 && SeqDLock==0)
    		{
    			if(Val==1)
				{
					MotorSeqB();
					CommandSuccessful=1;
					UART_SendStr("Command parsed. Sequence B initiated \n \r");
				}
    			else if(Val==0)
				{
					MotorSequenceInterrupt();CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
				}
    		}
			else
			{
				CommandSuccessful=1;
				UART_SendStr("Warning: Sequence conflict occurring \n \r");
			}
    	}
    	else if(strcmp(ExternObj,"SeqC")==0)
		{
    		if(SeqALock==0 && SeqBLock==0 && SeqCLock==0 && SeqDLock==0)
			{
    			if(Val==1)
				{
    				MotorSeqC();
    				CommandSuccessful=1;
					UART_SendStr("Command parsed. Sequence C initiated \n \r");
				}
    			else if(Val==0)
				{
					MotorSequenceInterrupt();CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
				}
			}
    		else
    		{
    			CommandSuccessful=1;
				UART_SendStr("Warning: Sequence conflict occurring \n \r");
    		}
		}
    	else if(strcmp(ExternObj,"SeqD")==0)
		{
    		if(SeqALock==0 && SeqBLock==0 && SeqCLock==0 && SeqDLock==0)
			{
    			if(Val==1)
    			{
					MoveMotorSeq();
					CommandSuccessful=1;
					UART_SendStr("Command parsed. Full sequence initiated \n \r");
    			}
    			else if(Val==0)
				{
					MotorSequenceInterrupt();CommandSuccessful=1;
					UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
				}
			}
    		else
    		{
    			CommandSuccessful=1;
				UART_SendStr("Warning: Sequence conflict occurring \n \r");
    		}
		}
    	else if(strcmp(ExternObj,"SeqE")==0)
    			{
    	    		if(SeqELock==0)
    				{
    	    			if(Val==1)
    	    			{
    						MoveMotorSeqPM1();
    						CommandSuccessful=1;
    						UART_SendStr("Command parsed. Full sequence for PM1 initiated \n \r");
    	    			}
    	    			else if(Val==0)
    					{
    						MotorSequenceInterrupt();CommandSuccessful=1;
    						UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
    					}
    				}
    	    		else
    	    		{
    	    			CommandSuccessful=1;
    					UART_SendStr("Warning: Sequence conflict occurring \n \r");
    	    		}
    			}
    	else
    	{
    		UART_SendStr("Warning ExtenObj was not recognised \n \r");
    	}
    }
    else if(strcmp(Command,"Get")==0)
    {
    	/*****Get Commands*****/
    	if(strcmp(ExternObj,"SeqAADC")==0)
    	{
    		sprintf(str,"SeqA ADC value: %i \n \r",SeqA_ADC);
			CommandSuccessful=1;
			UART_SendStr(str);
    	}
    	else if(strcmp(ExternObj,"SeqCADC")==0)
		{
    		sprintf(str,"SeqC ADC value: %i \n \r",SeqC_ADC);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"CalibADC")==0)
		{
    		sprintf(str,"Calibration ADC value: %i \n \r",Calib1_ADC);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"CalibSteps")==0)
		{
    		sprintf(str,"Calibration steps: %i \n \r",CalibSteps);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"SeqErrorCode")==0)
		{
    		sprintf(str,"Sequence error code: %i \n \r",SeqErrorCode);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LTapeMotion")==0)
		{
    		sprintf(str,"Tape length : %.2f [mm] \n \r",(double)L_TapeMotion/1e3);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"TTapeMotion")==0)
		{
    		sprintf(str,"Sequence execute time: %.2f [s] \n \r",(double)T_TapeMotion/1e3);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"SequenceCount")==0)
		{
    		sprintf(str,"Sequence count: %i \n \r",SequenceCount);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LockA")==0)
		{
			sprintf(str,"LockA: %i \n \r",SeqALock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LockB")==0)
		{
			sprintf(str,"LockB: %i \n \r",SeqBLock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LockC")==0)
		{
			sprintf(str,"LockC: %i \n \r",SeqCLock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LockD")==0)
		{
			sprintf(str,"LockD: %i \n \r",SeqDLock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"LockE")==0)//MatchTensionLock
		{
			sprintf(str,"LockD: %i \n \r",SeqDLock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"MTLock")==0)//MatchTensionLock
		{
			sprintf(str,"MTLock: %i \n \r",MatchTensionLock);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"ADCALower")==0)
		{
			sprintf(str,"ADCALower: %i \n \r",T1.adc_lowerval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"ADCAHigher")==0)
		{
			sprintf(str,"ADCAHigher: %i \n \r",T1.adc_upperval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"ADCBLower")==0)
		{
			sprintf(str,"ADCBLower: %i \n \r",T2.adc_lowerval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
    	else if(strcmp(ExternObj,"ADCBHigher")==0)
		{
			sprintf(str,"ADCBHigher: %i \n \r",T2.adc_upperval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"ADCCLower")==0)
		{
			sprintf(str,"ADCCLower: %i \n \r",T3.adc_lowerval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"ADCCHigher")==0)
		{
			sprintf(str,"ADCCHigher: %i \n \r",T3.adc_upperval);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MSAOuter")==0)
		{
			sprintf(str,"MSAOuter: %i \n \r",MS1.R0);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MSBOuter")==0)
		{
			sprintf(str,"MSBOuter: %i \n \r",MS2.R0);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MTAOuter")==0)
		{
			sprintf(str,"MTAOuter: %i \n \r",MT1.R0);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MTBOuter")==0)
		{
			sprintf(str,"MTBOuter: %i \n \r",MT2.R0);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MSAInner")==0)
		{
			sprintf(str,"MSAInner: %i \n \r",MS1.Ri);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MSBInner")==0)
		{
			sprintf(str,"MSBInner: %i \n \r",MS2.Ri);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MTAInner")==0)
		{
			sprintf(str,"MTAInner: %i \n \r",MT1.Ri);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"MTBInner")==0)
		{
			sprintf(str,"MTBInner: %i \n \r",MT2.Ri);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"SeqE_Lower")==0)
		{
			sprintf(str,"SeqE_Lower: %i \n \r",SeqE_Lower);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"SeqE_Upper")==0)
		{
			sprintf(str,"SeqE_Upper: %i \n \r",SeqE_Upper);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"SeqE_NSteps")==0)
		{
			sprintf(str,"SeqE_Upper: %i \n \r",SeqE_Upper);
			CommandSuccessful=1;
			UART_SendStr(str);
		}
		else if(strcmp(ExternObj,"DevInfo")==0)
		{
			UART_SendStr("PM2 Embedded code \n \r");
			CommandSuccessful=1;
		}
    	//MatchTensionDirec=0;int MatchTensionADC=0;int MatchTensionStepCounter=0;double MatchTensionTolerance=0.1;MatchTensionID=0;
    	//MTDirec,MTADC,MTTolerance,MTID
		else if(strcmp(ExternObj,"MTDirec")==0)
		{
			sprintf(str,"MTDirec: %i \n \r",MatchTensionDirec);
			UART_SendStr(str);
			CommandSuccessful=1;
		}
		else if(strcmp(ExternObj,"MTStep")==0)
		{
			sprintf(str,"MTStep: %i \n \r",MatchTensionStepCounter);
			UART_SendStr(str);
			CommandSuccessful=1;
		}
		else if(strcmp(ExternObj,"MTADC")==0)
		{
			sprintf(str,"MTADC: %i \n \r",MatchTensionADC);
			UART_SendStr(str);
			CommandSuccessful=1;
		}
		else if(strcmp(ExternObj,"MTTolerance")==0)
		{
			sprintf(str,"MTTolerance: %i \n \r",MatchTensionTolerance);
			UART_SendStr(str);
			CommandSuccessful=1;
		}
		else if(strcmp(ExternObj,"MTID")==0)
		{
			sprintf(str,"MTID: %i \n \r",MatchTensionID);
			UART_SendStr(str);
			CommandSuccessful=1;
		}
    	else
    	{
    		sprintf(str,"Warning ExternObj not recognised \n \r");
			CommandSuccessful=1;
			UART_SendStr(str);
    	}
    }
    else if(strcmp(Command,"Set")==0)
    {
    	/*****Set Commands*****/
    	if(strcmp(ExternObj,"SeqAADC")==0)
		{
    		SeqA_ADC=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqA_ADC set \n \r");
		}
		else if(strcmp(ExternObj,"SeqCADC")==0)
		{
			SeqC_ADC=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqC_ADC set \n \r");
		}
		else if(strcmp(ExternObj,"CalibADC")==0)
		{
			Calib1_ADC=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. Calib_ADC set \n \r");
		}
		else if(strcmp(ExternObj,"CalibSteps")==0)
		{
			CalibSteps=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. CalibSteps set \n \r");
		}
		else if(strcmp(ExternObj,"SeqErrorCode")==0)
		{
			SeqErrorCode=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqErrorCode set \n \r");
		}
		else if(strcmp(ExternObj,"LTapeMotion")==0)
		{
			L_TapeMotion=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. L_TapeMotion set \n \r");
		}
		else if(strcmp(ExternObj,"TTapeMotion")==0)
		{
			T_TapeMotion=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. T_TapeMotion set \n \r");
		}
		else if(strcmp(ExternObj,"ADCALower")==0)
		{
			T1.adc_lowerval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCALower set \n \r");
		}
		else if(strcmp(ExternObj,"ADCAHigher")==0)
		{
			T1.adc_upperval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCAHigher set \n \r");
		}
		else if(strcmp(ExternObj,"ADCBLower")==0)
		{
			T2.adc_lowerval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCBLower set \n \r");
		}
		else if(strcmp(ExternObj,"ADCBHigher")==0)
		{
			T2.adc_upperval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCBHigher set \n \r");
		}
		else if(strcmp(ExternObj,"ADCCLower")==0)
		{
			T3.adc_lowerval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCCLower set \n \r");
		}
		else if(strcmp(ExternObj,"ADCCHigher")==0)
		{
			T3.adc_upperval=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. ADCCHigher set \n \r");
		}

		else if(strcmp(ExternObj,"MSARInner")==0)
		{
			MS1.Ri=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MSARInner set \n \r");
		}

		else if(strcmp(ExternObj,"MSBRInner")==0)
		{
			MS2.Ri=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MSBROuter set \n \r");
		}
		else if(strcmp(ExternObj,"MTARInner")==0)
		{
			MT1.Ri=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTAROuter set \n \r");
		}
		else if(strcmp(ExternObj,"MTBRInner")==0)
		{
			MT2.Ri=Val;CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTBROuter set \n \r");
		}
		else if(strcmp(ExternObj,"SeqE_Lower")==0)
		{
			SeqE_Lower=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqE_Lower set \n \r");
		}
		else if(strcmp(ExternObj,"SeqE_Upper")==0)
		{
			SeqE_Upper=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqE_Upper set \n \r");
		}
		else if(strcmp(ExternObj,"SeqE_NSteps")==0)
		{
			SeqE_NSteps=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. SeqE_NSteps set \n \r");
		}
    	//MatchTensionDirec=0;int MatchTensionADC=0;int MatchTensionStepCounter=0;double MatchTensionTolerance=0.1;MatchTensionID=0;
    	//MTDirec,MTADC,MTTolerance,MTID
		else if(strcmp(ExternObj,"MTDirec")==0)
		{
			MatchTensionDirec=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTDirec set \n \r");
		}
		else if(strcmp(ExternObj,"MTADC")==0)
		{
			MatchTensionADC=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTADC set \n \r");
		}
		else if(strcmp(ExternObj,"MTTolerance")==0)
		{
			MatchTensionTolerance=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTTolerance set \n \r");
		}
		else if(strcmp(ExternObj,"MTID")==0)
		{
			MatchTensionID=Val;
			CommandSuccessful=1;
			UART_SendStr("Command successfully parsed. MTID set \n \r");
		}
    }
    else if(strcmp(Command,"Calibrate")==0)
	{
    	if(CalibMotorLock==0)
    	{	if(strcmp(ExternObj,"SeqAll")==0)
			{
				if(Val==1)
				{
					CalibrateMotors();
					UART_SendStr("Command successfully parsed. Calibrating motors \n \r");
				}
				else if(Val==0)
				{
					MotorSequenceInterrupt();
					UART_SendStr("Command successfully parsed. Motor sequence stopped \n \r");
				}
			}
    	}
    	else
    	{
    		UART_SendStr("Warning calib is current occuring \n \r");
    	}

	}
    if(CommandSuccessful==0)
    {
    	UART_SendStr("Warning command was not parsed from GUI.\n \r");
    }
    parsedone = 1;
	return;
}

