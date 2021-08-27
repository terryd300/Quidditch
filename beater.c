//
// Created by Terry Delaney on 3/27/2021.
//

#include "beater.h"


/* Beater Actions
 * Run infinite loop
 * Pick a random active player
 * Send SIGUSR1
 * Take a short sleep period
*/

void * beater()
{
    // Unblock signals and set signal handlers

    sigemptyset(&beatersignal);
    sigaddset(&beatersignal, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &beatersignal, NULL);

    beaterkill.sa_handler = beaterhit;
    beaterkill.sa_flags = 0;

    while (*gameactive == 0) //Wait for game to start
    {
    }

    while (*gameactive == 1)
    {
        srand(time(NULL));
        playerselection = rand() % 7 - 1;

        if (activeplayers[playerselection] != 0 && pthread_equal(pthread_self(), beateronethread[0]) || pthread_equal(pthread_self(), beateronethread[1]))
        {
            // Send SIGUSR 1
            pthread_kill( activeplayers[playerselection], SIGUSR1);
            blockmsg(playerselection);
        }

        else if (activeplayers[playerselection] != 0 && pthread_equal(pthread_self(), beatertwothread[0]) || pthread_equal(pthread_self(), beatertwothread[1]))
        {
            // Send SIGUSR1
            pthread_kill( activeplayers[playerselection + 7], SIGUSR1);
            blockmsg(playerselection + 7);
        }

        // Sleep for up to 5 seconds

        srand(time(NULL));
        beatersleep = rand() % 5000;
        usleep(beatersleep);
    }

    return 0;
}

void blockmsg()
{
    switch (playerselection)
    {
        case 0: message(logfile, "Team 1 Beater attempted to block Chaser 1.");
            break;

        case 1: message(logfile, "Team 1 Beater attempted to block Chaser 2.");
            break;

        case 2: message(logfile, "Team 1 Beater attempted to block Chaser 3.");
            break;

        case 3: message(logfile, "Team 1 Beater attempted to block Beater 1.");
            break;

        case 4: message(logfile, "Team 1 Beater attempted to block Beater 2.");
            break;

        case 5: message(logfile, "Team 1 Beater attempted to block Keeper.");
            break;

        case 6: message(logfile, "Team 1 Beater attempted to block Seeker.");
            break;

        case 7: message(logfile, "Team 2 Beater attempted to block Chaser 1.");
            break;

        case 8: message(logfile, "Team 2 Beater attempted to block Chaser 2.");
            break;

        case 9: message(logfile, "Team 2 Beater attempted to block Chaser 3.");
            break;

        case 10: message(logfile, "Team 2 Beater attempted to block Beater 1.");
            break;

        case 11: message(logfile, "Team 2 Beater attempted to block Beater 2.");
            break;

        case 12: message(logfile, "Team 2 Beater attempted to block Keeper.");
            break;

        case 13: message(logfile, "Team 2 Beater attempted to block Seeker.");
            break;

        default:
            break;
    }
}

void beaterhit()
{
    sigfillset(&beatersignal);
    pthread_sigmask(SIG_BLOCK, &beatersignal, &oldsignalset);
    sigemptyset(&beatersignal);
    sigaddset(&beatersignal, SIGUSR1);
    pthread_sigmask(SIG_UNBLOCK, &beatersignal, NULL);
    blocked = sleep(2);

    if (blocked == 0)
    {
        for (int i = 3; i < 12; i++)
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
            case 3: message(logfile, "Beater 1 on Team 1 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 4: message(logfile, "Beater 2 on Team 1 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 10: message(logfile, "Beater 1 on Team 2 has been hit by the Bludger and has fallen off their broomstick.");
                break;

            case 11: message(logfile, "Beater 2 on Team 2 has been hit by the Bludger and has fallen off their broomstick.");
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