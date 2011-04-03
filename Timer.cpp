/*
 *  Timer.cpp
 *  C++ Timer
 *
 *  Created by Sam Gray on 5/11/10.
 *  Copyright 2010 Sam Gray. All rights reserved.
 *
 */

#include "Timer.h"

void Timer::startTimer(float inInterval, bool inRepeat, void *inClassVoidPtr, void (*inFunctionVoidPtr)(void *, void **), int numOfVals, ...)
{
    /* set everything, and create what's needed */
    interval = inInterval;
    classPointer = inClassVoidPtr;
    voidFunction = (*inFunctionVoidPtr);
    repeat = inRepeat;
    numOfVoids = numOfVals;
    voidArray = new void*[numOfVoids];
    pthread_t threadID;
    
    va_list list;
    va_start(list, numOfVals);
    
    int i;
    for(i = 0; i < numOfVoids; i++)
    {
        voidArray[i] = va_arg(list, void *);
    }
    
    va_end(list);
    
    if(pthread_create(&threadID, NULL, Timer::TimerMain, (void *)this) != 0)
    {
        printf("pthread_create() failed!\n");
    }
}

void *Timer::TimerMain(void *inTimer)
{
	Timer *timer = (Timer *)inTimer;
	
	if (timer->repeat == true) 
	{
		for (;timer->repeat != false;) 
		{
			usleep(timer->interval * MAC_CONVERSION);
			if(timer->repeat != false)
			timer->voidFunction(timer->classPointer, timer->voidArray);
		}
	}
	else 
	{
		usleep(timer->interval * MAC_CONVERSION);
		timer->voidFunction(timer->classPointer, timer->voidArray);
	}
    
	pthread_detach(pthread_self());
	pthread_exit(0);
}

void Timer::killTimer(void)
{
	repeat = false;
}