//
// Created by cgutech on 18-10-29.
//

#include <pthread.h>
#include "timer/timer_1ms.h"

OneMsTimer* OneMsTimer::_pInstance = NULL;

void *OneMsTimer::ThreadProc(void *pParam) {
    ((OneMsTimer*)pParam)->ThreadProc();
    return nullptr;
}

void OneMsTimer::ThreadProc() {
    while (mIsRun) {
        OneMSTimerProc();
        usleep(1000);
    }
}


void OneMsTimer::OneMSTimerProc() {
    m_1ms_timer++;
}

__uint32_t OneMsTimer::Get_1ms_timer() {
    return m_1ms_timer;
}
__uint32_t OneMsTimer::Get_interval_time(__uint32_t time) {
    if (m_1ms_timer >= time)
        return (m_1ms_timer - time);
    else
        return (0xffffffff - time + m_1ms_timer + 1);
}

void OneMsTimer::Start() {
    mIsRun = true;
    pthread_create(&mThreadId, NULL, ThreadProc, this);
}

void OneMsTimer::Stop() {
    mIsRun = false;
    pthread_join(mThreadId, NULL);
    pthread_detach(mThreadId);
}

void OneMsTimer::SetEventCallback(IOneMsTimerCallback *callback) {
    _pEventCallback = callback;
}

