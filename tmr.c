/********************************************************************/
/*                                                                  */
/* (C) Copyright IBM UK Ltd. 1996                                   */
/*                                                                  */
/* TMR   - Example of DosTmrQueryTime and DosTmrQueryFreq usage.    */
/*                                                                  */
/* Query the high resolution timer.                                 */
/* Richard Moore 16th November 98                                   */
/* Version 1.0                                                      */
/*                                                                  */
/* Syntax TMR <none>                                                */
/*                                                                  */
/*                                                                  */
/********************************************************************/



#define INCL_DOSPROFILE

#include <os2.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*************************************************************************************/
/*                                                                                   */
/* Purpose:                                                                          */
/*                                                                                   */
/* DosTmrQueryTime queries the 64-bit high resolution timer.                         */
/*                                                                                   */
/* DosTmrQueryFreq queries the frequency of the high resolution timer.               */
/* Subtracting two 64-bit times and dividing by the frequency will give the          */
/* high resolution time interval in seconds.                                         */
/*                                                                                   */
/*************************************************************************************/

/*************************************************************************************/
/*                                                                                   */
/*      Prototype definitions for DosTmrQueryTime and DosTmrQueryFreq                */
/*                                                                                   */
/*************************************************************************************/
/*                                                                                   */
/*   APIRET APIENTRY DosTmrQueryTime(PQWORD time);                                   */
/*   APIRET APIENTRY DosTmrQueryFreq(PULONG freq);                                   */
/*                                                                                   */
/*************************************************************************************/

/*************************************************************************************/
/*                                                                                   */
/* DosTmrQueryTime returns the following return codes:                               */
/*                                                                                   */
/*************************************************************************************/
/*                                                                                   */
/* 0       NO_ERROR                                                                  */
/* 87      ERROR_INVALID_PARAMETER                                                   */
/* 99      ERROR_DEVICE_IN_USE                                                       */
/* 535     ERROR_TMR_NO_DEVICE                                                       */
/* 536     ERROR_TMR_INVALID_TIME                                                    */
/*                                                                                   */
/*************************************************************************************/

/*************************************************************************************/
/*                                                                                   */
/* DosTmrQueryFreq returns the following return codes:                               */
/*                                                                                   */
/*************************************************************************************/
/*                                                                                   */
/* 0       NO_ERROR                                                                  */
/* 87      ERROR_INVALID_PARAMETER                                                   */
/* 99      ERROR_DEVICE_IN_USE                                                       */
/* 535     ERROR_TMR_NO_DEVICE                                                       */
/*                                                                                   */
/*************************************************************************************/

void int3(void);

int main(int argc, char *argv[], char *envp[])
{
   QWORD start_time;  
   QWORD end_time;  
   QWORD interval;

   ULONG freq;
   APIRET rc;

   rc=DosTmrQueryTime(&start_time);
   printf("DosTmrQueryTime rc=%u time=0x%08x%08x\n",rc,start_time.ulHi,start_time.ulLo);
                 
   DosSleep(100);
   printf("Sleeping 100ms\n");
   
   rc=DosTmrQueryTime(&end_time);
   printf("DosTmrQueryTime rc=%u time=0x%08x%08x\n",rc,end_time.ulHi,end_time.ulLo);
   
   rc=DosTmrQueryFreq(&freq);
   printf("DosTmrQueryFreq rc=%u freq=%uHz\n",rc,freq);

   interval.ulLo = end_time.ulLo - start_time.ulLo;
   interval.ulHi = (end_time.ulLo >= start_time.ulLo) ? end_time.ulHi - start_time.ulHi: end_time.ulHi - start_time.ulHi - 1;
   printf("Time interval=0x%08x%08x units=%uns\n",interval.ulHi,interval.ulLo,1000000000/freq);
   if (interval.ulHi == 0) printf("Appox. %uns\n",interval.ulLo*(1000000000/freq));
   
   return 0;
}

