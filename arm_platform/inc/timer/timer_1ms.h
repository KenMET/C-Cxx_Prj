//
// Created by cgutech on 18-10-29.
//

#ifndef __TIMER_1MS_H__
#define __TIMER_1MS_H__


#include <stdint.h>
#include <cstddef>
#include <zconf.h>


#define ONE_MS_TIMER_ENABLE

class IOneMsTimerCallback {
public:
    virtual ~IOneMsTimerCallback(){}
    virtual void OneMsEvent() = 0;
};

class OneMsTimer
{
public:
    __uint32_t Get_1ms_timer();
    __uint32_t Get_interval_time(__uint32_t time);
    static OneMsTimer* GetInstance() {
        if(_pInstance == NULL) {
            _pInstance = new OneMsTimer();
        }
        return _pInstance;
    }
    void Start();
    void SetEventCallback(IOneMsTimerCallback* callback);
    void Stop();
private:
    OneMsTimer(){
    }
    static OneMsTimer* _pInstance;
    IOneMsTimerCallback* _pEventCallback;

    static void* ThreadProc(void* pParam);
    void ThreadProc();
    bool mIsRun;
    __uint32_t m_1ms_timer;
    pthread_t mThreadId;

    void OneMSTimerProc();
};

#endif //__TIMER_1MS_H__
