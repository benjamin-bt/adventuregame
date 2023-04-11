#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common.h"
#include "dir.h"
#include "playstate.h"
#include "item.h"
#include "display.h"

void showItemsAtPlace(struct PlayState *playState)
{
    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];

        if (item->location == playState->currentPlaceId)
        {
            if (!item->isFound)
            {
                if (strlen(item->asciiart) > 0)
                {
                    displayAsciiArt(playState, item->asciiart);
                }

                printf("\n%s\r\n", item->description);
                item->isFound = true;
            }
            else
            {
                printf("%s\r\n", item->shortdescription);
            }

            break;
        }
    }
}

void tryToPick(struct PlayState *playState)
{
    bool isThereAnyItems = false;

    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];
        if (item->location == playState->currentPlaceId)
        {
            if (!isThereAnyItems) printf("\nYou see something here: ");
            printf("%s ", item->title);
            isThereAnyItems = true;
        }
    }

    if (!isThereAnyItems)
    {
        printf("\nThere is nothing to pick!\n");
        return;
    }

    char buffer[255];
    printf("\nWhich item do you pick up? ");
    scanf("%s",(char *) &buffer);

    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];
        if (item->location == playState->currentPlaceId && strncmp(item->title, buffer, strlen(buffer))==0)
        {
            if((playState->backpack + item->weight) <= MAXWEIGHT)
            {
                printf("\nYou picked %s up!\n", item->title);
                item->location = 0;
                playState->backpack += item->weight;
            }
            else
            {
                printf("\nYou cannot carry this much!\n");
            }
                return;
        }
    }
}

void tryToDrop(struct PlayState *playState)
{
    bool isThereAnyItems = false;

    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];
        if (item->location == 0)
        {
            if (!isThereAnyItems) printf("\nYou have some items in your inventory: \n");
            printf("%s ", item->title);
            isThereAnyItems = true;
        }
    }

    if (!isThereAnyItems)
    {
        printf("\nThere is nothing to drop!\n");
        return;
    }

    char buffer[255];
    printf("\nWhich item do you drop? ");
    scanf("%s",(char *) &buffer);

    for (int i=1; i<= playState->numberOfItems; i++)
    {
        struct Item *item = &playState->items[i];
        if (item->location == 0 && strncmp(item->title, buffer, strlen(buffer))==0)
        {
            printf("\nYou dropped %s !\n", item->title);
            item->location = playState->currentPlaceId;
            playState->backpack -= item->weight;
            return;
        }
    }

    printf("\nThere is nothing like that to drop!\n");
}

void readItemsFromFile(struct PlayState *playState)
{
    char folder[255];
    sprintf(folder, "%s%s\\items\\",playState->dataRoot, playState->currentQuest);

    playState->numberOfItems = countFilesInFolder(folder);

    playState->items = (struct Item*)malloc ((playState->numberOfItems + 1) * sizeof(struct Item));

    for (int i=1; i<=playState->numberOfItems; i++)
    {
        readItemFromFile(folder, i, playState->items+i);
    }
}

void readItemFromFile(char *folder, int i, struct Item *item)
{
    char filename[255];
    FILE *fp;
    char buffer[255];

    sprintf(filename, "%s%d.item", folder, i);
    fp = fopen(filename, "r");

    fgets(buffer, sizeof(buffer), fp);
    strncpy(item->title, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(item->shortdescription, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(item->description, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(item->asciiart, buffer, max(strlen(buffer)-1,0));

    fscanf(fp, "%d", &item->location);

    fscanf(fp, "%d", &item->weight);

    int holdToWin;
    fscanf(fp, "%d", &holdToWin);
    item->holdToWin = (holdToWin != 0);

    fclose(fp);
}
