//
// Created by lewis on 21/04/2021.
//

#include "games.h"
#include <stdio.h>

void testHorizontalGameWin();
void testVerticalWin();
void testEntry();


int main(int argc, char **argv)
{
    testHorizontalGameWin();
    testVerticalWin();
    testEntry();

    printf("\n\n\nWorking...");

    return 0;
}

void testVerticalWin() {
    //Create Game Struct
    Game game = {
            .name1 = "player1",
            .name2 = "player2",
            .rowSize = 7,
            .columnSize = 6,
            .board = constructLinkedMatrix(7,6),
            .pTurn = 1,
            .log = newEntry(NULL, 0, 0),
            .gameType = 0
    };

    insertCoin(game, 1, 2);
    insertCoin(game, 1, 1);
    insertCoin(game, 1, 1);
    insertCoin(game, 1, 1);
    insertCoin(game, 1, 1);
    insertCoin(game, 1, 2);

    displayBoard(game.board, 6);

    if (checkWinConditions(&game)) {
        printf("\nHorizontal WINNER");
    }
}

void testHorizontalGameWin() {
    //Create Game Struct
    Game game = {
            .name1 = "player1",
            .name2 = "player2",
            .rowSize = 7,
            .columnSize = 6,
            .board = constructLinkedMatrix(7,6),
            .pTurn = 1,
            .log = newEntry(NULL, 0, 0),
            .gameType = 0
    };

    insertCoin(game, 1, 2);
    insertCoin(game, 2, 1);
    insertCoin(game, 3, 1);
    insertCoin(game, 4, 1);
    insertCoin(game, 5, 1);
    insertCoin(game, 6, 2);

    displayBoard(game.board, 6);

    if (checkWinConditions(&game)) {
        printf("\nHorizontal WINNER");
    }
}

void testEntry() {
    struct Entry * log = newEntry(NULL, 0, 0);
    newEntry(log, 1,1);
    newEntry(log, 2,2);
    newEntry(log, 2,2);
    newEntry(log, 2,2);
    newEntry(log, 4,1);
    newEntry(log, 2,1);
    printf("\nEntry seems to work...");
}