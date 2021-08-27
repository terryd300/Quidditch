//
// Created by Terry Delaney on 3/27/2021.
//

#include "quaffle.h"

/* Quaffle Actions
 * Run an infinite loop
 * Pick a Random Chaser
 * Send SIGUSR2
*/

void * quaffle()
{
    while (*gameactive == 0)
        pause();

    while (*gameactive == 1)
    {
        srand(time(NULL));
        playerselection = rand() % 3;
        teamselection = rand() % 2;

        sprintf(quafflemsg, "The Quaffle has been caught by Chaser #%d on Team %d", playerselection, teamselection);
        message(logfile, quafflemsg);
        pthread_kill(activeplayers[playerselection + 7 * teamselection], SIGUSR2);
    }

    return 0;
}