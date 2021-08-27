#include "HW6.h"

int main()
{

    // Clear The Screen
    system("clear");

    // Initialize Global Variables

    teamonescore = (int *) malloc (sizeof(int));
    teamtwoscore = (int *) malloc (sizeof(int));
    caught_snitch = (int *) malloc (sizeof(int));
    gameactive = (int *) malloc (sizeof(int));
    activeplayers = (pthread_t *) malloc (14 * sizeof(pthread_t));    // Player identifiers in activeplayers.txt
    goals = (pthread_t *) malloc (2 * sizeof(pthread_t));

    *teamonescore = 0;
    *teamtwoscore = 0;
    *caught_snitch = 0;
    *gameactive = 0;


    // Purpose of logfile is a place to keep a history of all thread calls and all responses
    logfile = fopen("log.txt", "w");

    // Block all signals before creating threads so that all threads have all signals blocked by default

    sigfillset(&blockallsignals);
    sigprocmask(SIG_BLOCK, &blockallsignals, NULL);

    // Create Threads

    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&chaseronethread[i], NULL, chaser, NULL) == 0)
        {
            sprintf(msg, "Team 1 Chaser %d created successfully.", i);
            message(logfile, msg);
            activeplayers[i] = chaseronethread[i];
        }
        else
        {
            printf("Failed to create Team 1 Chaser %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&chasertwothread[i], NULL, chaser, NULL) == 0)
        {
            sprintf(msg, "Team 2 Chaser %d created successfully.", i);
            message(logfile, msg);
            activeplayers[i + 7] = chasertwothread[i];
        }
        else
        {
            printf("Failed to create Team 2 Chaser %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&beateronethread[i], NULL, beater, NULL) == 0)
        {
            sprintf(msg, "Team 1 Beater %d created successfully.", i);
            message(logfile, msg);
            activeplayers[i + 3] = beateronethread[i];
        }
        else
        {
            printf("Failed to create Team 1 Beater %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&beatertwothread[i], NULL, beater, NULL) == 0)
        {
            sprintf(msg, "Team 2 Beater %d created successfully.", i);
            message(logfile, msg);
            activeplayers[i + 10] = beatertwothread[i];
        }
        else
        {
            printf("Failed to create Team 2 Beater %d\n", i);
            return 1;
        }
    }

    if (pthread_create(&seekeronethread, NULL, seeker, NULL) == 0)
    {
        message(logfile, "Team 1 Seeker created successfully.");
        activeplayers[5] = seekeronethread;
    }
    else
    {
        printf("Failed to create Team 1 Seeker\n");
        return 1;
    }

    if (pthread_create(&seekertwothread, NULL, seeker, NULL) == 0)
    {
        message(logfile, "Team 2 Seeker created successfully.");
        activeplayers[12] = seekertwothread;
    }
    else
    {
        printf("Failed to create Team 2 Seeker\n");
        return 1;
    }

    if (pthread_create(&keeperonethread, NULL, keeper, NULL) == 0)
    {
        message(logfile, "Team 1 Keeper created successfully.");
        activeplayers[6] = keeperonethread;
    }
    else
    {
        printf("Failed to create Team 1 Keeper\n");
        return 1;
    }

    if (pthread_create(&keepertwothread, NULL, keeper, NULL) == 0)
    {
        message(logfile, "Team 2 Keeper created successfully.");
        activeplayers[13] = keepertwothread;
    }
    else
    {
        printf("Failed to create Team 2 Keeper\n");
        return 1;
    }

    if (pthread_create(&quafflethread, NULL, quaffle, NULL) == 0)
    {
        message(logfile, "Quaffle created successfully.");
    }
    else
    {
        printf("Failed to create Quaffle\n");
        return 1;
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&bludgerthread[i], NULL, bludger, NULL) == 0)
        {
            sprintf(msg, "Bludger %d creates successfully.", i);
            message(logfile, msg);
        }
        else
        {
            printf("Failed to create Bludger %d\n", i);
            return 1;
        }
    }

    if (pthread_create(&snitchthread, NULL, snitch, NULL) == 0)
    {
        message(logfile, "Golden Snitch created successfully.");
    }
    else
    {
        printf("Failed to create Golden Snitch\n");
        return 1;
    }

    if (pthread_create(&goalonethread, NULL, goal, NULL) == 0)
    {
        message(logfile, "Goal 1 created successfully.");
        goals[0] = goalonethread;
    }
    else
    {
        printf("Failed to create Goal 1\n");
        return 1;
    }

    if (pthread_create(&goaltwothread, NULL, goal, NULL) == 0)
    {
        message(logfile, "Goal 2 created successfully.");
        goals[1] = goaltwothread;
    }
    else
    {
        printf("Failed to create Goal 2\n");
        return 1;
    }

    // Start Game

    message(logfile, "All threads have been created successfully!\n\nThe Game is about to start!\n");
    printf("The game is starting in ");

    for (int i = 5; i >= 0; i--)
    {
        printf("%d...", i);
    }

    printf("\n");

    refreshscoreboard();
    *gameactive = 1;
    *numberofactiveplayers = 14;
    printf("Game is active");


    return 0;
}

