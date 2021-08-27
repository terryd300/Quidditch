//
// Created by Terry Delaney on 3/27/2021.
//

#include "seeker.h"

/* Seeker Actions
 * Wake Up
 * Check Snitch Status
 * Go to Sleep
 * If seeker is able to catch the snitch, Add 150 points to the respective team's score and end the game
*/

void * seeker()
{
    // Unblock signals and set signal handlers

    sigemptyset(&seekersignal);
    sigaddset(&seekersignal, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &seekersignal, NULL);

    seekeraction.sa_handler = seekerhit;
    seekeraction.sa_flags = 0;

    while (*gameactive == 0)
    {
    }

    while (*gameactive == 1)
    {
        if (*caught_snitch % 2 == 1)
        {
            if (pthread_equal(pthread_self(), activeplayers[6]))
            {
                message(logfile, "Team 1's seeker has caught the Golden Snitch!");
                *teamonescore += 150;
                endgame();
            }
            else
            {
                message(logfile, "Team 2's seeker has caught the Golden Snitch!");
                *teamtwoscore += 150;
                endgame();
            }
        }

        // Sleep for up to 15 seconds

        srand(time(NULL));
        seekersleep = rand() % 15000;
        usleep(seekersleep);
    }

    return 0;
}

void seekerhit()
{
    sigfillset(&seekersignal);
    pthread_sigmask(SIG_BLOCK, &seekersignal, &oldsignalset);
    sigemptyset(&seekersignal);
    sigaddset(&seekersignal, SIGUSR1);
    pthread_sigmask(SIG_UNBLOCK, &seekersignal, NULL);
    blocked = sleep(2);

    if (blocked == 0)
    {
        if (pthread_equal(pthread_self(), activeplayers[6]))
        {
            playerselection = 6;
        }
        else
        {
            playerselection = 13;
        }
        activeplayers[playerselection] = 0;
        numberofactiveplayers--;

        switch (playerselection)
        {
            case 6:
                message(logfile, "Team 1's Seeker has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 13:
                message(logfile, "Team 2's Seeker has been hit by the Bludger and has fallen off their broomstick.");
                break;

            default:
                break;
        }

        if (numberofactiveplayers == 0)
        {
            endgame();
        }
        else
        {
            pthread_kill(pthread_self(), SIGKILL);
        }
    }
    else
    {
        sigfillset(&seekersignal);
        pthread_sigmask(SIG_BLOCK, &seekersignal, NULL);
        pthread_sigmask(SIG_UNBLOCK, &oldsignalset, NULL);
    }
}
