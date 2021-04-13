#include <stdio.h>

//Game Header File
#include "games.h"

char menuSelection;

void startGame();
void otherOption();

void menu(){

    printf("\nWelcome to Connect Four - CLI Edition!\n\nPlease select from the menu then press enter...\n\n1. Start Game\n2. Other Option\n0. Exit\nChoice:  ");
    fgets(&menuSelection,8,stdin);

    switch (menuSelection) {
        case '0':
            return;
            break;
        case '1':
            startGame();
            break;
        case '2':
            otherOption();
            break;

        default:
            printf("Invalid Choice... %c", menuSelection);
            break;
    }
}


int main(int argc, char **argv)
{
    //menu();

    int numberOfColumns = 7, numberOfRows = 5;
    struct Position* board;
    board = createBoard(0, 0, numberOfColumns, numberOfRows);

    displayBoard(board);
    return 0;
}

void startGame(){
    printf("\nStart Game\n");
}

void otherOption(){
    printf("\n1Other Option\n");
}