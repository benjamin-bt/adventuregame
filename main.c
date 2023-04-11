#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dir.h"
#include "playstate.h"
#include "config.h"
#include "place.h"
#include "item.h"
#include "enemy.h"
#include "game.h"
#include "menu.h"

void randomize();

struct PlayState mPlayState;

int main()
{
    randomize();

    readConfigFromFile(&mPlayState);

    strcpy(mPlayState.currentQuest, "castle");

//playGame(&mPlayState);
    displayMenu(&mPlayState);
}

void randomize()
{
    time_t t;

    srand((unsigned) time(&t));
}
