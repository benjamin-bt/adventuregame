#include<stdbool.h>
#ifndef ENEMY_H
#define ENEMY_H

#include "playstate.h"

struct Enemy
{
    char title[32];
    char shortdescription[255];
    char description[255];
    char asciiart[255];
    int locationId;
    bool isMet;
    bool isMoving;
    bool beKilledToWin;
};

int meetEnemyAtPlace(struct PlayState *playState);
bool combatEnemyIfOneIsMet(struct PlayState *playState);
void moveEnemies(struct PlayState *playState);
void readEnemiesFromFile(struct PlayState *playState);
void readEnemyFromFile(char *folder, int i, struct Enemy *enemy);

#endif
