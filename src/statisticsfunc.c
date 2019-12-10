/*
 * statisticsfunc.c
 *
 *  Created on: 20 Oct 2017
 *      Author: svr11
 */

#include "statisticsfunc.h"
/*
 *
 * Some averaging and array statistics functions
 * */
double MaxArray(int* InputArray)
{
    int Temp=0;
    int i=0;
    for(i=0;i<ARRAYLEN;i++)
    {
     if(InputArray[i]>Temp)
     {
         Temp=InputArray[i];
     }
     else
     {
         //Do nothing
     }
    }
    return (double)Temp;
}
float MinArray(int* InputArray)
{
    int Temp=4096;
    int i=0;
    for(i=0;i<ARRAYLEN;i++)
    {
     if(InputArray[i]<Temp)
     {
         Temp=InputArray[i];
     }
     else
     {

     }
    }
    return (float)Temp;
}
int MeanArray(int* InputArray)
{
    float Temp=0;int Result;
    int i=0;
    for(i=0;i<ARRAYLEN;i++)
    {
    	if(InputArray[i]<1 || InputArray[i]>4095)
    	{
    		Temp+=0.0;
    	}
    	else
		{
    		Temp+=InputArray[i];
		}

    }
    Temp=Temp/ARRAYLEN;
    Result=(int)Temp;
    return Result;
}
int StdArray(int* InputArray)
{
    float MeanVal=0;int Result;float Temp=0;
    int i=0;
    //Calulate mean array
    for(i=0;i<ARRAYLEN;i++)
    {
    	if(InputArray[i]<1 || InputArray[i]>4095)
    	{
    		MeanVal+=0.0;
    	}
    	else
		{
    		MeanVal+=InputArray[i];
		}

    }
    MeanVal=MeanVal/ARRAYLEN;
    i=0;
    //Now calculate the standard deviation of sample
	for(i=0;i<ARRAYLEN;i++)
	{
		if(InputArray[i]<1 || InputArray[i]>4095)
		{
			Temp+=0.0;
		}
		else
		{
			Temp+=(MeanVal-InputArray[i])*(MeanVal-InputArray[i]);
		}

	}
	Temp=sqrt(Temp/(ARRAYLEN-1));
    Result=(int)Temp;
    return Result;
}

void ZeroArray(int* InputArray)
{
	float Temp=0;int Result;
	int i=0;
	for(i=0;i<ARRAYLEN;i++)
	{
		InputArray[i]=0;
	}
	return;
}

