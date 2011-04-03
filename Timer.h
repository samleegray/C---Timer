/*
 *  Timer.h
 *  C++ Timer
 *
 *  Created by Sam Gray on 5/11/10.
 *  Copyright 2010 Sam Gray. All rights reserved.
 *
 */

#include <iostream>
#include <unistd.h>
#include <pthread.h>

#define MAC_CONVERSION 1000000

class Timer
{
public:
	//C/static C++ function timer functions
	/*void startTimer(float inInterval, bool inRepeat, void (*inFunction)());*/
    void startTimer(float inInterval, bool inRepeat, void *inClassVoidPtr, void (*inFunctionVoidPtr)(void *, void **), int numOfVals, ...);
    static void *TimerMain(void *inTimer);
    void killTimer(void);
	
private:
	//C & C++ timer shared variables
    void *classPointer;
    void (*voidFunction)(void *, void **);
    void **voidArray;
    int numOfVoids;
	float interval;
	bool repeat;
};