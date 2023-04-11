#ifndef PLAYSTATE_H
#define PLAYSTATE_H

struct PlayState {
    char dataRoot[255];
    char savedRoot[255];
    char currentQuest[255];
    int numberOfPlaces;
    int numberOfEnemies;
    int numberOfItems;

    struct Place *places;
    struct Item *items;
    struct Enemy *enemies;

    int currentPlaceId;
    int stamina;
    int backpack;
};

#endif
