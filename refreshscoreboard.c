//
// Created by Terry Delaney on 4/4/2021.
//

#include "refreshscoreboard.h"

void refreshscoreboard()
{
    system ("clear");

    message(logfile, "Gryffindor\t\tSlytherin");
    sprintf(scoreone, "%d", *teamonescore);
    sprintf(scoretwo, "%d", *teamtwoscore);
    strcpy (text, scoreone);
    strcat (text, "\t\t\t");
    strcat (text, scoretwo);
    message (logfile, text);

}