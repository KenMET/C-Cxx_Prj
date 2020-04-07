//
// Created by ken on 19-08-03.
//

#include <unistd.h>
#include <pthread.h>
#include "business/business.h"
#include "timer/timer_1ms.h"

#include "log.h"

void Thread_test::ThreadProc(void){ 
	int count = 0;
	OneMsTimer *Instance = OneMsTimer::GetInstance();
	__uint32_t start_time = Instance->Get_1ms_timer();
	while(1){
		usleep(1000);
		if(++count == 100){
			count = 0;
			LOG_WARN("Thread[%s] Exit[%d]", this->GetDescription(), Instance->Get_interval_time(start_time)); 
			this->ThreadStop();
		}
	}
}


void MainThread::ThreadProc(void){ 
	int count = 0;
	char text[64];

//#ifdef ONE_MS_TIMER_STATE
	OneMsTimer *Instance = OneMsTimer::GetInstance();
	Instance->Start();
//#endif

	while(1){
		usleep(100000);
		sprintf(text, "Test(%d)", count++);
		Thread_test *Thread_number = new Thread_test(text);
		Thread_number->ThreadStart(false);
	}
}

