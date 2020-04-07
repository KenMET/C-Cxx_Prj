//
// Created by ken on 19-08-03.
//

#ifndef __APP_BASIC_CLASS_H__
#define __APP_BASIC_CLASS_H__

#include <iostream> 
#include <cstring>
using namespace std;

class AppBasic
{
public :
    AppBasic(const char * text = "default"){
        description = new char[strlen(text) + 1];
        memcpy(description, text, strlen(text));
        description[strlen(text)] = 0;
    }
	~AppBasic(){
        delete description;
    }

    static void* ThreadProc(void* pParam);
    virtual void ThreadProc(void){
        cout << "This is basic app thread" <<endl;
    }

    char *GetDescription(void){
        return  description;
    }
    void ThreadStart(bool joinable);
    void ThreadWaitExit();
    void ThreadStop();

    void test_func(void);

    pthread_t mThreadId;

private:
    char *description;
    bool mIsRun;
    
};
#endif //__APP_BASIC_CLASS_H__
