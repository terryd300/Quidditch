//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_GOAL_H
#define HW_6_GOAL_H

#include "HW6.h"

void * goal();
void score();


struct sigaction goalaction;
int blockedshot;
int choice;
sigset_t goalsignal;
sigset_t oldsignalset;

#endif //HW_6_GOAL_H
