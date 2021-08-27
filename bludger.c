//
// Created by Terry Delaney on 3/27/2021.
//

#include "bludger.h"

/* Bludger Actions
 * Mostly Sleeping
 * Pick 1 Random Player
 * Send SIGINT
 * Sleep for a random period of time
*/

void * bludger()
{

    while (*gameactive == 0) //Wait for game to start
    {
    }

    while (*gameactive == 1)
    {
        srand(time(NULL));
        playerselection = rand() % 14 - 1;

        pthread_kill(activeplayers[playerselection], SIGINT);
        strikemsg();

        // Sleep for up to 10 seconds

        srand(time(NULL));
        bludgersleep = rand() % 10000;
        usleep(bludgersleep);
    }

        return 0;
}

void strikemsg()
{
    switch (playerselection)
    {
        case 0: message(logfile, "Bludger attempted to strike Chaser 1 on Team 1.");
            break;

        case 1: message(logfile, "Bludger attempted to strike Chaser 2 on Team 1.");
            break;

        case 2: message(logfile, "Bludger attempted to strike Chaser 3 on Team 1.");
            break;

        case 3: message(logfile, "Bludger attempted to strike Beater 1 on Team 1.");
            break;

        case 4: message(logfile, "Bludger attempted to strike Beater 2 on Team 1.");
            break;

        case 5: message(logfile, "Bludger attempted to strike the Keeper on Team 1.");
            break;

        case 6: message(logfile, "Bludger attempted to strike the Seeker on Team 1.");
            break;

        case 7: message(logfile, "Bludger attempted to strike Chaser 1 on Team 2.");
            break;

        case 8: message(logfile, "Bludger attempted to strike Chaser 2 on Team 2.");
            break;

        case 9: message(logfile, "Bludger attempted to strike Chaser 3 on Team 2.");
            break;

        case 10: message(logfile, "Bludger attempted to strike Beater 1 on Team 2.");
            break;

        case 11: message(logfile, "Bludger attempted to strike Beater 2 on Team 2.");
            break;

        case 12: message(logfile, "Bludger attempted to strike the Keeper on Team 2.");
            break;

        case 13: message(logfile, "Bludger attempted to strike the Seeker on Team 2.");
            break;

        default:
            break;
    }
}