#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "playstate.h"
#include "enemy.h"
#include "place.h"
#include "item.h"
#include "game.h"

void saveGame(struct PlayState *playState)
{
    char filename[255];

    printf("Type a savefile name (max 10 characters): ");
    scanf("%s", (char *) &filename);

    char name[255];
    FILE *fp;

    sprintf(name, "%s%s.txt", playState->savedRoot, filename);

    fp = fopen(name, "w");
    fprintf(fp, "%s\n", playState->currentQuest);
    fprintf(fp, "%d\n", playState->currentPlaceId);
    fprintf(fp, "%d\n", playState->stamina);

    for(int i = 1; i <= playState->numberOfEnemies; i++)
    {
        fprintf(fp, "%d\n", playState->enemies[i].locationId);
        fprintf(fp, "%d\n", playState->enemies[i].isMet);
    }

    for(int j = 1; j <= playState->numberOfPlaces; j++)
    {
        fprintf(fp, "%d\n", playState->places[j].isVisited);
    }

    for(int k = 1; k <= playState->numberOfItems; k++)
    {
        fprintf(fp, "%d\n", playState->items[k].location);
    }

    fclose(fp);

    printf("Game is saved to %s.txt\n", filename);
    /*k
      0) filenév létrehozása (quest név + '_' + dátum + idõ)
      1)1 file megnyitása írásra
      2) quest name beleírása elsõ sorba
      3) currentplaceid beleírás köv sorba

   4) ciklus a PlayState minden enemy-jén.
     a) sor írása fileba, fprintf-fel ami két mezõt tartalmaz (locationid, ismet)

   5) ciklus a PlayState minden itemjén-jén.
     a) sor írása fileba, fprintf-fel ami egy mezõt tartalmaz (locationid)

   6) ciklus a PlayState minden place-én.
     a) sor írása fileba, fprintf-fel ami egy mezõt tartalmaz (isvisited)

    */
}

void loadGame(struct PlayState *playState)
{

    char filename[255];

    printf("Type a savefile name (max 10 characters): ");
    scanf("%s", (char *) &filename);

    char name[255];
    FILE *fp;

    sprintf(name, "%s%s.txt", playState->savedRoot, filename);

    fp = fopen(name, "r");

    fscanf(fp, "%s", playState->currentQuest);

    initGame(playState);

    fscanf(fp, "%d", &playState->currentPlaceId);

    fscanf(fp, "%d", &playState->stamina);

    int tmp;

    for(int i = 1; i <= playState->numberOfEnemies; i++)
    {
        fscanf(fp, "%d", &playState->enemies[i].locationId);

        fscanf(fp, "%d", &tmp);
        playState->enemies[i].isMet = (tmp != 0);
    }

    for(int j = 1; j <= playState->numberOfPlaces; j++)
    {
        fscanf(fp, "%d", &tmp);
        playState->places[j].isVisited = (tmp != 0);
    }

    for(int k = 1; k <= playState->numberOfItems; k++)
    {
        fscanf(fp, "%d", &playState->items[k].location);
    }

    fclose(fp);
   /*
   1) file megnyitása

   2) elsõ sor a quest neve
   2a) második sor a currentplaceid

   3) quest nevének beírása a playState.questname mezõbe
   4) initGame meghívása  (betöltõdnek a struktúrák)
   5) ciklus a PlayState minden enemy-jén.
     a) sor beolvasás fileból, fscanf-fel ami két mezõt tartalmaz (locationid, ismet)

   6) ciklus a PlayState minden itemjén-jén.
     a) sor beolvasás fileból, fscanf-fel ami egy mezõt tartalmaz (locationid)

   7) ciklus a PlayState minden place-én.
     a) sor beolvasás fileból, fscanf-fel ami egy mezõt tartalmaz (isvisited)

   */
}
