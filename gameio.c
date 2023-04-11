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
      0) filen�v l�trehoz�sa (quest n�v + '_' + d�tum + id�)
      1)1 file megnyit�sa �r�sra
      2) quest name bele�r�sa els� sorba
      3) currentplaceid bele�r�s k�v sorba

   4) ciklus a PlayState minden enemy-j�n.
     a) sor �r�sa fileba, fprintf-fel ami k�t mez�t tartalmaz (locationid, ismet)

   5) ciklus a PlayState minden itemj�n-j�n.
     a) sor �r�sa fileba, fprintf-fel ami egy mez�t tartalmaz (locationid)

   6) ciklus a PlayState minden place-�n.
     a) sor �r�sa fileba, fprintf-fel ami egy mez�t tartalmaz (isvisited)

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
   1) file megnyit�sa

   2) els� sor a quest neve
   2a) m�sodik sor a currentplaceid

   3) quest nev�nek be�r�sa a playState.questname mez�be
   4) initGame megh�v�sa  (bet�lt�dnek a strukt�r�k)
   5) ciklus a PlayState minden enemy-j�n.
     a) sor beolvas�s fileb�l, fscanf-fel ami k�t mez�t tartalmaz (locationid, ismet)

   6) ciklus a PlayState minden itemj�n-j�n.
     a) sor beolvas�s fileb�l, fscanf-fel ami egy mez�t tartalmaz (locationid)

   7) ciklus a PlayState minden place-�n.
     a) sor beolvas�s fileb�l, fscanf-fel ami egy mez�t tartalmaz (isvisited)

   */
}
