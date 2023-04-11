#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "playstate.h"
#include "config.h"

void readConfigFromFile(struct PlayState *playState)
{
    FILE *fp;
    char buffer[255];

    fp = fopen("game.config", "r");

    fscanf(fp, "%s", buffer);
    strcpy(playState->dataRoot, buffer);

    fscanf(fp, "%s", buffer);
    strcpy(playState->savedRoot, buffer);

    fclose(fp);
}

