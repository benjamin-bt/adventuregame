#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#include "display.h"
#include "conio2.h"
#include "playstate.h"
#include "game.h"
#include "place.h"
#include "item.h"
#include "enemy.h"
#include "rockpaper.h"
#include "gameio.h"

static const int MAXSTAMINA = 3;


void initGame(struct PlayState *playState)
{
    readPlacesFromFile(playState);
    readItemsFromFile(playState);
    readEnemiesFromFile(playState);

    playState->currentPlaceId = 1;
    playState->stamina = MAXSTAMINA;
    playState->backpack = 0;
}

void playGame(struct PlayState *playState)
{
    bool exit = false;

    char command[255];

    while (!exit)
    {
        struct Place *currentPlace = &playState->places[playState->currentPlaceId];

        printHeader(playState);
        showPlaceDetails(playState);
        showItemsAtPlace(playState);

        if(winGame(playState))
            break;

        if(combatEnemyIfOneIsMet(playState))
            break;

        printf("\nWhat is your next move? ");
        scanf("%s", (char *) &command);

        int wannabePlaceId = -1;

        if(strcmp(command, "n") == 0 || strcmp(command, "north") == 0)
        {
            wannabePlaceId = currentPlace->directions[0];
        }
        else if(strcmp(command, "e") == 0 || strcmp(command, "east") == 0)
        {
            wannabePlaceId = currentPlace->directions[1];
        }
        else if(strcmp(command, "s") == 0 || strcmp(command, "south") == 0)
        {
            wannabePlaceId = currentPlace->directions[2];
        }
        else if(strcmp(command, "w") == 0 || strcmp(command, "west") == 0)
        {
            wannabePlaceId = currentPlace->directions[3];
        }
        else if(strcmp(command, "exit") == 0)
        {
            exit = true;
        }
        else if(strcmp(command, "save") == 0)
        {
            saveGame(playState);
        }
        else if(strcmp(command, "rest") == 0)
        {
            tryToRest(playState);
        }
        else if(strcmp(command, "pick") == 0)
        {
            tryToPick(playState);
        }
        else if(strcmp(command, "drop") == 0)
        {
            tryToDrop(playState);
        }
        else
        {
            printf("\nI can not do that!\r\n");
            Sleep(2);
        }

        if (wannabePlaceId == 0)
        {
            printf("\nYou can not go there!\r\n");
            Sleep(2);
        }
        else if (wannabePlaceId > 0)
        {
            playState->currentPlaceId = wannabePlaceId;
        }

        moveEnemies(playState);
    }

    return;
}


bool winGame(struct PlayState *playState)
{
    struct Place *currentPlace = &playState->places[playState->currentPlaceId];
    if(!currentPlace->beHereToWin)
        return false;

    for (int i=1; i<= playState->numberOfEnemies; i++)
    {
        struct Enemy *enemy = &playState->enemies[i];
        if (enemy->beKilledToWin && enemy->locationId != 0)
            return false;
    }

    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];
        if (item->holdToWin && item->location != 0)
            return false;
    }

    displayAsciiArt(playState, "win.asc");
    return true;
}

void tryToRest(struct PlayState *playState)
{
    struct Place *currentPlace = &playState->places[playState->currentPlaceId];
    if(playState->stamina < MAXSTAMINA)
    {
        if(currentPlace->isSafePlace)
        {
            printf("\nYou have slept a bit. You already feel better.\n");
            playState->stamina++;
        }
        else
        {
            printf("\nThis place is not safe to rest.\n");
        }
    }
    else
    {
        printf("\nYou are so fit!\n");
    }
}

void printHeader(struct PlayState *playState)
{
    clearScreen();

    textcolor(LIGHTCYAN);
    printf("STAMINA: %d ", playState->stamina);
    textcolor(WHITE);

    struct Place *currentPlace = &playState->places[playState->currentPlaceId];
    textcolor(YELLOW);
    printf("PLACE: %s ", currentPlace->title);
    textcolor(WHITE);

    textcolor(LIGHTGREEN);
    printf("BACKPACK: %d ", playState->backpack);
    textcolor(WHITE);

    printf("\n---------------------\n");
}
