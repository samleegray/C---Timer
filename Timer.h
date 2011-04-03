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

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <vector>

#define MAC_CONVERSION 1000000

using namespace std;

class Timer
{
public:
	//C/static C++ function timer functions
	/*void startTimer(float inInterval, bool inRepeat, void (*inFunction)());*/
    void startTimer(float inInterval, bool inRepeat, void *inClassVoidPtr, void (*inFunctionVoidPtr)(void *, vector<void *>), int numOfVals, ...);
    static void *TimerMain(void *inTimer);
    void killTimer(void);
	
private:
	//C & C++ timer shared variables
    void *classPointer;
    void (*voidFunction)(void *, vector<void *>);
    void **voidArray;
    vector<void *> voidVector;
    int numOfVoids;
	float interval;
	bool repeat;
    pthread_t threadID;
};