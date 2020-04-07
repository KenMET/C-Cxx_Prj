//
// Created by ken on 19-08-03.
//

#ifndef __BUSINESS_H__
#define __BUSINESS_H__

#include <iostream> 
#include <cstring>
using namespace std;

#include "app_basic/app_basic.h"

class Thread_test: public AppBasic{
public:
	Thread_test(const char *text = "null"):AppBasic(text) { 

	}
	void ThreadProc(void);
};


class MainThread: public AppBasic{
public:
	MainThread(const char *text = "MainThread"):AppBasic(text) { 

	}
	void ThreadProc(void);
};


#endif //__BUSINESS_CLASS_H__
