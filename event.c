#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include "event.h"

int make_timer(timer_t *timerID, int sec, int msec, void (*function)()){  
    struct sigevent te;  
    struct itimerspec its;  
    struct sigaction sa;  
    int sigNo = SIGRTMIN;  
   
    /* Set up signal handler. */  
    sa.sa_flags = SA_SIGINFO;  
    // sa.sa_sigaction = timer_handler;
    sa.sa_sigaction = function;  
    sigemptyset(&sa.sa_mask);  
  
    if (sigaction(sigNo, &sa, NULL) == -1){  
        printf("sigaction error\n");
        return -1;  
    }  
   
    /* Set and enable alarm */  
    te.sigev_notify = SIGEV_SIGNAL;  
    te.sigev_signo = sigNo;  
    te.sigev_value.sival_ptr = timerID;  
    timer_create(CLOCK_REALTIME, &te, timerID);  
   
    its.it_interval.tv_sec = sec;
    its.it_interval.tv_nsec = msec * 1000000;  
    its.it_value.tv_sec = sec;
    
    its.it_value.tv_nsec = msec * 1000000;
    timer_settime(*timerID, 0, &its, NULL);  
   
    return 0;  
}