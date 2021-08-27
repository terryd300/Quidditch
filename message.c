//
// Created by Terry Delaney on 4/1/2021.
//

#include "message.h"

/* Message Purpose
 * The purpose of Message is to output messages to both stdout and to the logfile with one command
*/

void * message(FILE *logfile, char msg[])
{
    fprintf(logfile, "%s\n", msg);
    printf("%s\n", msg);

    return 0;
}