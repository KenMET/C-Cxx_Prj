//
// Created by cgutech on 18-10-29.
//

#include <pthread.h>
#include "app_basic/app_basic.h"


void *AppBasic::ThreadProc(void *pParam) {
    ((AppBasic*)pParam)->ThreadProc();
    return nullptr;
}

void AppBasic::ThreadStart(bool joinable) {
    mIsRun = true;
    pthread_create(&mThreadId, NULL, ThreadProc, this);
    if(!joinable){
        pthread_detach(mThreadId);
    }
}

void AppBasic::ThreadWaitExit() {
    pthread_join(mThreadId, NULL);
}

void AppBasic::ThreadStop() {
    mIsRun = false;
    pthread_exit(NULL);
}

