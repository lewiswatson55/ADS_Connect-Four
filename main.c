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
    //newGame("Lewis", "Kate", 7, 6);



    //struct Position *board = createBoard(0,0,3,3);
    struct Position *board = constructLinkedMatrix(10,10);

//    Game game;
//    game.board = constructLinkedMatrix(7,6);
//    game.columnSize = 6;
//    game.rowSize = 7;
//
//    insertCoin(game.board, 1, 2);
//    insertCoin(game.board, 1, 1);
//    insertCoin(game.board, 1, 1);
//    insertCoin(game.board, 1, 1);
//    insertCoin(game.board, 1, 1);
//    insertCoin(game.board, 1, 2);
//
    displayBoard(board, 3);
//
//    if (checkWinConditions(&game)) {
//        printf("WINNER");
//    }

//    printf("\n\nCalls: %d\nValid: %d\n\n\n", count, valid);

//    struct Entry * log = newEntry(NULL, 0, 0);
//    newEntry(log, 1,1);
//    newEntry(log, 2,2);
//    newEntry(log, 2,2);
//    newEntry(log, 2,2);
//    newEntry(log, 4,1);
//    newEntry(log, 2,1);

    printf("\nWorking...");

    return 0;
}

void startGame(){
    printf("\nStart Game\n");
}

void otherOption(){
    printf("\n1Other Option\n");
}

void testMethod(){

}