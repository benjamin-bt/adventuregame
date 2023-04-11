#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "enemy.h"
#include "playstate.h"
#include "place.h"
#include "common.h"
#include "dir.h"
#include "display.h"
#include "rockpaper.h"
#include "game.h"

int meetEnemyAtPlace(struct PlayState *playState)
{
    int enemyId = 0;

    for (int i=1; i<= playState->numberOfEnemies; i++)
    {
        struct Enemy *enemy = &playState->enemies[i];
        if (enemy->locationId == playState->currentPlaceId)
        {
            if (!enemy->isMet)
            {
                if (strlen(enemy->asciiart) > 0)
                {
                    displayAsciiArt(playState, enemy->asciiart);
                }

                printf("\n%s\r\n", enemy->description);
                enemy->isMet = true;
            }
            else
            {
                printf("%s\r\n", enemy->shortdescription);
            }

            enemyId = i;
            break;
        }
    }
    return enemyId;
}

bool combatEnemyIfOneIsMet(struct PlayState *playState)
{
    int currentEnemyId = meetEnemyAtPlace(playState);
    if(currentEnemyId > 0)
    {
        if(playRockPaperScissors()==0)
        {
            if(--playState->stamina == 0)
            {
                displayAsciiArt(playState, "die.asc");
                return true;
            }
            else
            {
                printf("\nYou are badly hurt!\n\n");
            }
        }
        else
        {
            printf("\nYou have defeated the monster!\n\n");

            struct Enemy *enemy = &playState->enemies[currentEnemyId];
            enemy->locationId = 0;
        }
    }

    return false;
}

void moveEnemies(struct PlayState *playState)
{
    for (int i=1; i<= playState->numberOfEnemies; i++)
    {
        struct Enemy *enemy = &playState->enemies[i];
        if (enemy->isMoving && enemy->locationId != 0)
        {
            int locationId;
            while (true)
            {
                locationId = (rand() % playState->numberOfPlaces) + 1;
                if (!playState->places[locationId].isSafePlace) break;
            }

            enemy->locationId = locationId;
        }
    }
}

void readEnemiesFromFile(struct PlayState *playState)
{
    char folder[255];
    sprintf(folder, "%s%s\\enemies\\",playState->dataRoot, playState->currentQuest);

    playState->numberOfEnemies = countFilesInFolder(folder);

    playState->enemies = (struct Enemy*)malloc ((playState->numberOfEnemies + 1) * sizeof(struct Enemy));

    for (int i=1; i<=playState->numberOfEnemies; i++)
    {
        readEnemyFromFile(folder, i, playState->enemies+i);
    }
}

void readEnemyFromFile(char *folder, int i, struct Enemy *enemy)
{
    char filename[255];
    FILE *fp;
    char buffer[255];

    sprintf(filename, "%s%d.enemy",folder, i);
    fp = fopen(filename, "r");

    fgets(buffer, sizeof(buffer), fp);
    strncpy(enemy->title, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(enemy->shortdescription, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(enemy->description, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(enemy->asciiart, buffer, max(strlen(buffer)-1,0));

    int locationId;
    fscanf(fp, "%d", &locationId);
    enemy->locationId = locationId;

    int isMoving;
    fscanf(fp, "%d", &isMoving);
    enemy->isMoving = (isMoving != 0);

    int beKilledToWin;
    fscanf(fp, "%d", &beKilledToWin);
    enemy->beKilledToWin = (beKilledToWin != 0);

    enemy->isMet = false;

    fclose(fp);
}

