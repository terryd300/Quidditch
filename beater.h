//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_BEATER_H
#define HW_6_BEATER_H

#include "HW6.h"

void * beater();
void blockmsg();
void beaterhit();

struct sigaction beaterkill;
int playerselection;
int blocked;
int beatersleep;
sigset_t beatersignal;
sigset_t oldsignalset;

#endif //HW_6_BEATER_H
