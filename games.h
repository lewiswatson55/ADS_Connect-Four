//
// Created by lewis on 13/04/2021.
//

#ifndef ADSCOURSEWORK_GAMEBOARD_H
#define ADSCOURSEWORK_GAMEBOARD_H

#include <stdbool.h>

typedef struct {
    char *name1, *name2;
    int rowSize, columnSize;
    int gameType;
    struct Position* board;
    bool gameEnded;
} Game;

struct Position {
    int takenBy;
    struct Position *right, *down;
};

struct Position* createBoard(int column, int row, int numberOfColumns, int numberOfRows);
void newGame(char *player1, char *player2, int columns, int rows);
void displayBoard(struct Position* board, int width);
void moveController(Game game);
void gameController();
void player1Move(),player2Move();
void checkDown(),checkRight(),checkDiagonal();
void gravityMove(); //Animate dropping?

#endif //ADSCOURSEWORK_GAMEBOARD_H
