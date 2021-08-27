//
// Created by Terry Delaney on 3/27/2021.
//

#ifndef HW_6_HW6_H
#define HW_6_HW6_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "beater.h"
#include "bludger.h"
#include "chaser.h"
#include "goal.h"
#include "keeper.h"
#include "quaffle.h"
#include "seeker.h"
#include "snitch.h"
#include "message.h"
#include "refreshscoreboard.h"
#include "endgame.h"

int* teamonescore;
int* teamtwoscore;
int* caught_snitch;
int* gameactive;
int* numberofactiveplayers;
FILE* logfile;
char msg[256];
pthread_t* activeplayers;
pthread_t* goals;
sigset_t blockallsignals;

pthread_t chaseronethread[3];
pthread_t chasertwothread[3];
pthread_t beateronethread[2];
pthread_t beatertwothread[2];
pthread_t seekeronethread;
pthread_t seekertwothread;
pthread_t keeperonethread;
pthread_t keepertwothread;
pthread_t quafflethread;
pthread_t bludgerthread[2];
pthread_t snitchthread;
pthread_t goalonethread;
pthread_t goaltwothread;

int main();

#endif //HW_6_HW6_H
