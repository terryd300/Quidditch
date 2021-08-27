//
// Created by Terry Delaney on 3/27/2021.
//

#include "keeper.h"

/* Keeper Actions
 * Start Infinite Loop
 * Send SIGUSR1 to their goal
 * Go to sleep for a random period of time
*/

void * keeper()
{
    // Unblock signals and set signal handlers

    sigemptyset(&keepersignal);
    sigaddset(&keepersignal, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &keepersignal, NULL);

    keeperkill.sa_handler = keeperhit;
    keeperkill.sa_flags = 0;

    while (*gameactive == 0)
    {
    }

    while (*gameactive == 1)
    {
        if (pthread_equal(pthread_self(), goalonethread))
        {
            pthread_kill(goalonethread, SIGINT);
        }
        else
        {
            pthread_kill(goaltwothread, SIGINT);
        }

        // Sleep for up to 5 seconds

        srand(time(NULL));
        keepersleep = rand() % 5000;
        usleep(keepersleep);
    }
    return 0;
}

void keeperhit()
{
    sigfillset(&chasersignal);
    pthread_sigmask(SIG_BLOCK, &chasersignal, &oldsignalset);
    sigemptyset(&chasersignal);
    sigaddset(&chasersignal, SIGUSR1);
    pthread_sigmask(SIG_UNBLOCK, &chasersignal, NULL);
    blocked = sleep(2);

    if (blocked == 0)
    {
        if (pthread_equal(pthread_self(), activeplayers[5]))
        {
            playerselection = 5;
        }
        else
        {
            playerselection = 12;
        }
        activeplayers[playerselection] = 0;
        numberofactiveplayers --;

        switch (playerselection)
        {
            case 5: message(logfile, "Team 1's Keeper has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 12: message(logfile, "Team 2's Keeper has been hit by the Bludger and has fallen off their broomstick.");
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
        sigfillset(&chasersignal);
        pthread_sigmask(SIG_BLOCK, &chasersignal, NULL);
        pthread_sigmask(SIG_UNBLOCK, &oldsignalset, NULL);
    }

}