//
// Created by Terry Delaney on 3/27/2021.
//

#include "snitch.h"

/* Snitch Actions
 * Wake Up
 * Toggle Caught_Snitch flag
 * Go back to sleep
*/

void * snitch()
{
    while (*gameactive == 0)
    {
    }

    while (*gameactive == 1)
    {
        caught_snitch++;

        // Sleep for up to 5 seconds

        srand(time(NULL));
        snitchsleep = rand() % 5000;
        usleep(snitchsleep);
    }

    return 0;
}