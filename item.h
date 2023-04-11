#ifndef ITEM_H
#define ITEM_H

static const int MAXWEIGHT = 5;

struct Item
{
    char title[32];
    char shortdescription[255];
    char description[255];
    char asciiart[255];
    int location;
    bool isFound;
    int weight;
    bool holdToWin;
};

void readItemsFromFile(struct PlayState *playState);
void readItemFromFile(char *folder, int i, struct Item *item);
void tryToPick(struct PlayState *playState);
void tryToDrop(struct PlayState *playState);
void showItemsAtPlace(struct PlayState *playState);

#endif
