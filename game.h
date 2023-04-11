#ifndef GAME_H
#define GAME_H

void initGame(struct PlayState *playState);
void playGame(struct PlayState *playState);
int meetEnemyAtPlace(struct PlayState *playState);
void moveEnemies(struct PlayState *playState);
bool winGame(struct PlayState *playState);
void printHeader(struct PlayState *playState);
void tryToRest(struct PlayState *playState);

#endif
