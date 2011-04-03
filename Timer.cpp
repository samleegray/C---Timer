/* 
 Copyright (c) 2011 Samuel Lee Stewart Gray
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. 
 */

#include "Timer.h"

void Timer::startTimer(float inInterval, bool inRepeat, void *inClassVoidPtr, void (*inFunctionVoidPtr)(void *, vector<void *>), int numOfVals, ...)
{
    /* set everything, and create what's needed */
    interval = inInterval;
    classPointer = inClassVoidPtr;
    voidFunction = (*inFunctionVoidPtr);
    repeat = inRepeat;
    numOfVoids = numOfVals;
    voidArray = new void*[numOfVoids];
    
    va_list list;
    va_start(list, numOfVals);
    
    printf("START!\n");
    int i;
    for(i = 0; i < numOfVoids; i++)
    {
        //voidArray[i] = va_arg(list, void *);
        void *var = va_arg(list, void *);
        voidVector.push_back(var);
    }
    
    va_end(list);
    
    printf("float:%f int:%d\n", *(float *)voidVector.at(0), *(int *)voidVector.at(1));
    
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
			timer->voidFunction(timer->classPointer, timer->voidVector);
		}
	}
	else 
	{
		usleep(timer->interval * MAC_CONVERSION);
		timer->voidFunction(timer->classPointer, timer->voidVector);
	}
    
	pthread_detach(pthread_self());
	pthread_exit(0);
}

void Timer::killTimer(void)
{
    pthread_detach(threadID);
    pthread_cancel(threadID);
    voidVector.clear();
}