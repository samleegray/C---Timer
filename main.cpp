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
#include "Timer.h"

class Test2
{
public:
    void superTest(void);
};

void Test2::superTest(void)
{
    printf("super test!\n");
}

class Test
{
public:
    void doThis(void);
	static void staticCppFunction(void *classPointer, vector<void *> voidVector);
	void taduh(void);
};

void Test::doThis(void)
{
	/* create a new timer */
    Timer *newTimer = new Timer;
	/* do whatever variables you want to send along to the timer's call back functions */
    char *charPtr = "wow";
	int myInt = 500;
	float myFloat = 89.28745;
    
    Test2 *newTest = new Test2;
	
	/* start the timer
	 first parameter: the time in seconds to call the call back function
	 second parameter: do you want this timer to repeat? true = yes false = no
	 third parameter: the C++ class you want to access in the call back functions
	 fourth parameter: the call back function to be called everytime the time interval you specified has passed
	 fith parameter: the number(not 0 indexed) of variables your sending along
	 6th to infinity paramters: whatever you want to send */
    newTimer->startTimer(1, true, (void *)newTest, this->staticCppFunction, 3, (void *)&myFloat, (void *)&myInt, (void *)charPtr);
    
    char blah[20];
	fgets(blah, 20, stdin);
    
    newTimer->killTimer();
}

/* ALL callback functions must be declared as this one is, it must be declared as static, and have these two parameters */
void Test::staticCppFunction(void *classPointer, vector<void *> voidVector)
{	
	/* all the variables you sent along with the startTimer function get sent here, in the same order you sent them
	 they get put into the voidArray passed as a parameter here */
	
	float myFloat = *(float *)voidVector.at(0);
	int myInt = *(int *)voidVector.at(1);
	char *myChar = (char *)voidVector.at(2);
    
    printf("%f %d %s\n", myFloat, myInt, myChar);
    
	/* sent the class as a void pointer so then you can turn it back into the class you used, and have all the
	 class's methods and the class's variables */
    Test2 *test = (Test2 *)classPointer;
	test->superTest();
}

void Test::taduh(void)
{
	printf("TADUH!\n");
}

int main (int argc, char * const argv[]) 
{
	Test *test = new Test;
    test->doThis();
	
    return 0;
}
