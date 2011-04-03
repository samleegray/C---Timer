Example source code can be found in the main.cpp file. If you have any issues with this, please let me know. I have used this code in several of my other projects without issue. Enjoy! :)

This is licensed with the MIT license. The full license information can be found in LICENSE.txt.

Example code copied & pasted directly from main.cpp:

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
		static void staticCppFunction(void *classPointer, void **voidArray);
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
	}

	/* ALL callback functions must be declared as this one is, it must be declared as static, and have these two parameters */
	void Test::staticCppFunction(void *classPointer, void **voidArray)
	{	
		/* all the variables you sent along with the startTimer function get sent here, in the same order you sent them
		 they get put into the voidArray passed as a parameter here */
	
		float *myFloat = (float *)voidArray[0];
		int *myInt = (int *)voidArray[1];
		char *myChar = (char *)voidArray[2];
    
	    printf("%f %d %s\n", *myFloat, *myInt, myChar);
    
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
	
		char blah[20];
		fgets(blah, 20, stdin);
	
	    return 0;
	}