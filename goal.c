//
// Created by Terry Delaney on 3/27/2021.
//

#include "goal.h"

/* Goal Actions
 * When a SIGINT has been received
 * Start a 2 Second Timer
 * If SIGUSR1 has been not been received in the 2 seconds - Indicate Goal Scored
 * If SIGUSR1 has been received in the two seconds - Indicate Shot Blocked
*/

void * goal()
{
    sigemptyset(&goalsignal);
    sigaddset(&goalsignal, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &goalsignal, NULL);

    goalaction.sa_handler = score;
    chaseraction.sa_flags = 0;

    while (*gameactive == 0)
    {
        pause();
    }

    while (*gameactive == 1)
    {
        sigaction(SIGINT, &goalaction, NULL);
    }

    return 0;
}

void score()
{
    sigfillset(&goalsignal);
    pthread_sigmask(SIG_BLOCK, &chasersignal, &oldsignalset);
    sigemptyset(&goalsignal);
    sigaddset(&goalsignal, SIGUSR1);
    blockedshot = sleep(2);

    if (blockedshot == 0) {
        // Goal Scored
        if (pthread_equal(pthread_self(), goals[0]))
        {
            teamonescore += 10;
        }
        else
        {
            teamtwoscore += 10;
        }

        srand(time(NULL));
        choice = rand() % 5;

        switch (choice)
        {
            case 0:
                message(logfile, "Oh My God...What an Insane Goal!");
                break;

            case 1:
                message(logfile, "That Has to be the Most Insane Goal I Have Ever Seen on a Quidditch Field!\nThat will have to be one of SportCenter's Top Plays!!!!");
                break;

            case 2:
                message(logfile, "GOOOOOOOOOOOOOOOOAAAAAAAAAAAAAAAAALLLLLLLLLLLLLLLLLLL");
                break;

            case 3:
                message(logfile, "I Do Not Believe What I Have Just Seen!!!  GOOOOOAAAAAAALLLLLLLL!");
                break;

            case 4:
                message(logfile, "GOAL GOAL GOAL GOAL GOAL GOAL GOAL GOAL GOAL");
                break;

            default:
                break;
        }

        refreshscoreboard();

    }
    else    // Goal Blocked
    {
        srand(time(NULL));
        choice = rand() % 5;

        switch (choice)
        {
            case 0:
                message(logfile, "Oh My God...What an Insane Save!");
                break;

            case 1:
                message(logfile, "That Has to be the Most Insane Save I Have Ever Seen on a Quidditch Field!");
                break;

            case 2:
                message(logfile, "HOLY COW!!! What a Save with his Broom!");
                break;

            case 3:
                message(logfile, "I Do Not Believe What I Have Just Seen!!! WHAT A SAVE!!");
                break;

            case 4:
                message(logfile, "Did you see that save?? That was absolutely amazing!\nThat will be on SportsCenter tonight!");
                break;

            default:
                break;

        }

        sigfillset(&goalsignal);
        pthread_sigmask(SIG_BLOCK, &chasersignal, NULL);
        pthread_sigmask(SIG_UNBLOCK, &oldsignalset, NULL);
    }
}
