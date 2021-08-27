//
// Created by Terry Delaney on 4/2/2021.
//

#include "timer.h"

// This function is specifically for setting a timer and returning a SIGALRM to the calling thread

void timer(pthread_t thread, int seconds)
{
    sleep(seconds);
    pthread_kill(thread, SIGALRM);
}