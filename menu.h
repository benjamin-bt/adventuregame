#ifndef MENU_H
#define MENU_H

struct QuestInfo
{
    char name[255];
    char description[255];
};

void displayMenu (struct PlayState *playState);
void selectQuest(struct PlayState *playState);
void readQuestFromFile(char *folder, struct QuestInfo *questInfo);

#endif
