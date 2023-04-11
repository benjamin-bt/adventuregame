#ifndef DISPLAY_H
#define DISPLAY_H

#include "playstate.h"

void clearScreen();
int getCharFromConsole();
void printToConsoleWithColor(char *text, int color);
void displayAsciiArt(struct PlayState *playState, char *artName);

#endif
