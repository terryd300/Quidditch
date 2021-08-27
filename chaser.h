//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_CHASER_H
#define HW_6_CHASER_H

#include "HW6.h"

void * chaser();
void takeshot();
void chaserhit();

struct sigaction chaseraction;
struct sigaction chaserkill;
int playerselection;
int blocked;
sigset_t chasersignal;
sigset_t oldsignalset;

#endif //HW_6_CHASER_H
