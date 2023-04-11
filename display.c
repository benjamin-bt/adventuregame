#include <stdio.h>

#include "conio2.h"
#include "playstate.h"

void clearScreen()
{
    clrscr();
}

int getCharFromConsole()
{
    return getch();
}

void printToConsoleWithColor(char *text, int color)
{
    textcolor(color);
    printf(text);
    textcolor(WHITE);
}

void displayAsciiArt(struct PlayState *playState, char *artName)
{
    int c;
    FILE *fp;
    char filename[255];

    sprintf(filename, "%s%s\\%s\\%s", playState->dataRoot, playState->currentQuest, "art", artName);

    fp = fopen(filename, "r");
    if (fp) {
        while ((c = getc(fp)) != EOF)
            putchar(c);
        fclose(fp);
    }
}
