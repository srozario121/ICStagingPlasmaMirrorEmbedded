/*
 * motorfuncs.h
 *
 *  Created on: 20 Oct 2017
 *      Author: svr11
 */

#ifndef MOTORFUNCS_H_
#define MOTORFUNCS_H_

#include "UART.h"
#include "ADC.h"
//GPIO.h
/***** Variable declarations*****/
typedef struct MotorVar{
    int NoStepsLeft;
	int NoStepsCurr;
	int DirVal;
	int PrescalerVal;
	int MotorConnected;
	int MotorNumber;
	uint32_t MotorSpeed;
	int AbsoluteSteps;
	double R0;//in microns varying radius
	double Ri;//in microns spool radius
	int MMMT_TensionNo;
	int MMMTSwitch;
	int MMMTMaxLoopCounter;
	int MMMTDirec;
	int MMMTADC;
	int MMMTTol;
	int MMMTSequenceSteps;
	int MMMTLock;
    } MotorVar;

struct MotorVar MS1;
struct MotorVar MS2;
struct MotorVar MT1;
struct MotorVar MT2;
int InputVal,L_TapeMotion,T_TapeMotion,SeqA_ADC,SeqC_ADC,Calib1_ADC,CalibSteps,SeqErrorCode,SequenceCount;
int MatchTensionDirec,MatchTensionADC, MatchTensionStepCounter,MatchTensionTolerance,MatchTensionID;
int SeqE_Lower,SeqE_Upper,SeqE_NSteps;
//Lock bits
int SeqALock, SeqBLock, SeqCLock, SeqDLock, CalibMotorLock,SeqInterrupt,SeqELock;
int MatchTensionLock;
/***** Function declarations*****/
void MoveMotor(MotorVar *MX);

void MoveMotorSeq();void MoveMotorSeqPM1();

void SetMotorDir(MotorVar *MX,int val);void SetMotorSteps(MotorVar *MX,int val);
void SetMotorSpeed(MotorVar *MX,uint32_t val);

void StartMotorInterrupt(MotorVar *MX);void StopMotorInterrupt(MotorVar *MX);
void MotorsOff(MotorVar *MX);void ToggleMotor(MotorVar *MX,int Val);
void MotorSeqA();void MotorSeqB();void MotorSeqC();
void MatchTension(MotorVar *MX);
void MoveMotorMatchTension(MotorVar *MX,ADCTens *TX);
void MotorSequenceInterrupt();

void CalibrateMotors();
void CalbrateStepMS1();void CalbrateStepMS2();

int LengthToSteps(MotorVar *MX);int TimeOfSequenceToMotorPeriod(MotorVar *MX);

#endif /* MOTORFUNCS_H_ */
