//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_KEEPER_H
#define HW_6_KEEPER_H

#include "HW6.h"

void * keeper();
void keeperhit();

int keepersleep;
struct sigaction keeperkill;
sigset_t keepersignal;

#endif //HW_6_KEEPER_H
