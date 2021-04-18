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
    newGame("Lewis", "Kate", 7, 6);

    //struct Position *board = createBoard(0,0,3,3);
    //struct Position *board = constructLinkedMatrix(7,5);
    //displayBoard(board, 3);
    //printf("\n\nCalls: %d\nValid: %d\n\n\n", count, valid);

//    displayBoard(board, 5);
//
//    int aaa = 2;
//    insertCoin(board, aaa);
//    insertCoin(board, aaa);
//    insertCoin(board, aaa);
//    insertCoin(board, aaa);
//    insertCoin(board, aaa);
//    insertCoin(board, aaa);
//
//    displayBoard(board,5);

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