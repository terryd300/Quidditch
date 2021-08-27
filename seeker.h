//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_SEEKER_H
#define HW_6_SEEKER_H

#include "HW6.h"

void * seeker();
void seekerhit();

struct sigaction seekeraction;
sigset_t seekersignal;
sigset_t oldsignalset;
int playerselection;
int blocked;
int seekersleep;

#endif //HW_6_SEEKER_H
