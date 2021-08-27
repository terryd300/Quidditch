//
// Created by Terry Delaney on 3/27/2021.
//

#include "chaser.h"

/* Chaser Actions
 * Start Infinite Loop
 * When a SIGUSR2 is received, send a SIGINT signal to the opponent's goal
*/

void * chaser()
{
    // Unblock signals and set signal handlers

    sigemptyset(&chasersignal);
    sigaddset(&chasersignal, SIGINT);
    sigaddset(&chasersignal, SIGUSR2);
    pthread_sigmask(SIG_UNBLOCK, &chasersignal, NULL);

    chaseraction.sa_handler = takeshot;
    chaseraction.sa_flags = 0;
    chaserkill.sa_handler = chaserhit;
    chaserkill.sa_flags = 0;

    sigaction(SIGUSR2, &chaseraction, NULL);
    sigaction(SIGINT, &chaserkill, NULL);

    while (*gameactive == 0)
    {
        pause();
    }

    while (*gameactive == 1)
    {

    }

    return 0;
}

void takeshot()
{
    for (int i = 0; i < 9; i++)
    {
        if (pthread_equal(pthread_self(), activeplayers[i]))
        {
            playerselection = i;
            break;
        }
    }

    switch (playerselection)
    {
        case 0: pthread_kill(goals[1], SIGINT);
            message(logfile, "Chaser 1 on Team 1 takes a shot at Goal 2.");
            break;

        case 1: pthread_kill(goals[1], SIGINT);
            message(logfile, "Chaser 2 on Team 1 takes a shot at Goal 2.");
            break;

        case 2: pthread_kill(goals[1], SIGINT);
            message(logfile, "Chaser 3 on Team 1 takes a shot at Goal 2");
            break;

        case 7: pthread_kill(goals[0], SIGINT);
            message(logfile, "Chaser 1 on Team 2 takes a shot at Goal 1.");
            break;

        case 8: pthread_kill(goals[0], SIGINT);
            message(logfile, "Chaser 2 on Team 2 takes a shot at Goal 1.");
            break;

        case 9: pthread_kill(goals[0], SIGINT);
            message(logfile, "Chaser 3 on Team 2 takes a shot at Goal 1.");
            break;

        default:
            break;
    }
}

void chaserhit()
{
    sigfillset(&chasersignal);
    pthread_sigmask(SIG_BLOCK, &chasersignal, &oldsignalset);
    sigemptyset(&chasersignal);
    sigaddset(&chasersignal, SIGUSR1);
    pthread_sigmask(SIG_UNBLOCK, &chasersignal, NULL);
    blocked = sleep(2);

    if (blocked == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (pthread_equal(pthread_self(), activeplayers[i]))
            {
                playerselection = i;
                activeplayers[i] = 0;
                numberofactiveplayers --;
                break;
            }
        }

        switch (playerselection)
        {
            case 0: message(logfile, "Chaser 1 on Team 1 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 1: message(logfile, "Chaser 2 on Team 1 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 2: message(logfile, "Chaser 3 on Team 1 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 7: message(logfile, "Chaser 1 on Team 2 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 8: message(logfile, "Chaser 2 on Team 2 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 9: message(logfile, "Chaser 3 on Team 2 has been hit by the Bludger and has fallen off their broomstick.");
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