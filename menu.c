#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "playstate.h"
#include "dir.h"
#include "display.h"
#include "conio2.h"
#include "game.h"
#include "gameio.h"
#include "menu.h"


void displayMenu (struct PlayState *playState)
{
    bool quit = false;
    char menu_option;

    clearScreen();
    printToConsoleWithColor("        ADVENTURE GAME\n", LIGHTGREEN);
    printToConsoleWithColor("\n------------------------------\n\n", LIGHTGREEN);

    do
    {
        printf("Main Menu\n");
        printf("New Game (N)\n");
        printf("Load Game (L)\n");
        printf("Exit Game (X)\n");
        printf("\nPlease enter an option from the main menu: ");
        menu_option = (char) getCharFromConsole();
        //scanf("%c", &menu_option);
        printf("\n\n");

        switch(menu_option){

        case 'N':
        case 'n':
            selectQuest(playState);
            initGame(playState);
            playGame(playState);

            free(playState->places);
            free(playState->enemies);
            free(playState->items);
            break;
        case 'L':
        case 'l':
            loadGame(playState);
            playGame(playState);

            free(playState->places);
            free(playState->enemies);
            free(playState->items);
            break;
        case'X':
        case'x':
            quit = true;
            break;
        default:
            printf("\ninvalid input!\n");
                break;
        }

    } while(!quit);
}

void selectQuest(struct PlayState *playState)
{
    int questCount = countSubfoldersInFolder(playState->dataRoot);
    struct QuestInfo * questInfos = (struct QuestInfo *) malloc(questCount * sizeof(questInfos));
    char **questFolders = getSubfoldersInFolder(playState->dataRoot);

    for (int i = 0; i < questCount; i++)
    {
        strcpy((char *) &questInfos[i].name, questFolders[i]);
        readQuestFromFile(playState->dataRoot, questInfos + i);
        free(questFolders[i]);
    }

    while (true)
    {
        printf("\nChoose your quest:\n\n");
        for (int i = 0; i < questCount; i++)
        {
            printf("%s - %s\n", questInfos[i].name, questInfos[i].description);
        }

        char buffer[255];
        scanf("%s", (char *) &buffer);

        for (int i = 0; i < questCount; i++)
        {
            if(strcmp((char *) buffer, questInfos[i].name) == 0)
            {
                strcpy(playState->currentQuest, buffer);
                free(questInfos);
                return;
            }
        }
    }
    //listázd a quests könyvtár tartalmát valahogy (könyvtárakban levõ quest.info fájlban levõ quest nevet kellene kiírni)
//válassz azok közül egyet

}

void readQuestFromFile(char *folder, struct QuestInfo *questInfo)
{
    char filename[255];
    FILE *fp;
    char buffer[255];

    sprintf(filename, "%s%s\\quest.info",folder, questInfo->name);
    fp = fopen(filename, "r");

    fgets(buffer, sizeof(buffer), fp);
    strcpy(questInfo->description, buffer);

    fclose(fp);
}
