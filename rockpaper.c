#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "display.h"
#include "conio2.h"

#include "rockpaper.h"

const int rock = 0;
const int paper = 1;
const int scissors = 2;
bool firstCombat = true;

int playRockPaperScissors()
{
    if(firstCombat)
    {
        printf("\nThe monsters at this place have mastered rock-paper-scissors. Instead of fighting with weapons, they will play three rounds of it with you.\n");
        firstCombat = false;
    }

    int playerScore = 0;
    int computerScore = 0;
    int tie = 0;

    int i = 0;
    while(i++ < 3 || playerScore == computerScore)
    {
            printf("\nType r(rock) p(paper) or s(scissors): ");

            char input;
            scanf("\n%c", &input);

            RockPaperScissors(input, &playerScore, &computerScore, &tie);
    }

    printf("\n\nCombat over\n");
    printf("\nYou: %d   Enemy: %d  Tie: %d \n\n", playerScore, computerScore, tie);

    return playerScore > computerScore ?1 : 0;
}

void RockPaperScissors(char playerInput, int *playerScore, int *computerScore, int *tie)
{
    int computerInput = rand() % 2 + 0;

    int ps = 0;
    int cs = 0;
    int ts = 0;

    switch (playerInput)
    {
        case 'r':
                if (computerInput == paper) cs++;
                if (computerInput == scissors) ps++;
                if (computerInput == rock) ts++;

                break;

        case 'p':
                if (computerInput == paper) ts++;
                if (computerInput == scissors) cs++;
                if (computerInput == rock) ps++;

                break;

        case 's':
                if (computerInput == paper) ps++;
                if (computerInput == scissors) ts++;
                if (computerInput == rock) cs++;

                break;
    }

    if (cs){
        printToConsoleWithColor("You lost this round!\n", RED);
        (*computerScore)++;
    } else if (ps){
        printToConsoleWithColor("You won this round!\n", GREEN);
        (*playerScore)++;
    } else if (ts) {
        printToConsoleWithColor("It's a tie...\n", YELLOW);
        (*tie)++;
    }
}

