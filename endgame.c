//
// Created by Terry Delaney on 4/4/2021.
//

#include "endgame.h"

void endgame()
{
    refreshscoreboard();
    message(logfile, "The Game Has Ended.");

    if (teamonescore > teamtwoscore)
    {
        message(logfile, "The winner is: Team Gryffindor!");
    }

    else if (teamtwoscore > teamonescore)
    {
        message(logfile, "The winner is: Team Slytherin!");
    }

    else
    {
        message(logfile, "The game has ended in a Tie!");
    }

    fclose(logfile);

    for (int i = 0; i < 14; i++)
    {
        if (activeplayers[i] != 0)
        {
            pthread_kill(activeplayers[i], SIGKILL);
        }
    }

    pthread_kill(quafflethread, SIGKILL);
    pthread_kill(bludgerthread[0], SIGKILL);
    pthread_kill(bludgerthread[1], SIGKILL);
    pthread_kill(snitchthread, SIGKILL);
    pthread_kill(goalonethread, SIGKILL);
    pthread_kill(goaltwothread, SIGKILL);

}