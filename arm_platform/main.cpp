//
// Created by ken on 19-08-03.
//

#include <iostream>

#include "log.h"
#include "business/business.h"


int main(int argc, char* argv[])
{
	MainThread *Thread = new MainThread("MainThread");//No need to delete this object

	//this option will generate a zombie process
	//Thread->ThreadStart(false);
	//pthread_exit(NULL);

	//Prevent zombie process
	Thread->ThreadStart(true);
	Thread->ThreadWaitExit();

	return 0;
}

