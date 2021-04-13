//
// Created by lewis on 13/04/2021.
//

#ifndef ADSCOURSEWORK_GAMEBOARD_H
#define ADSCOURSEWORK_GAMEBOARD_H

typedef struct {
    char *name1, *name2;
    int rowSize, columnSize;
    struct Position* board;
} Game;

struct Position {
    int takenBy;
    struct Position *right, *down;
};

struct Position* createBoard(int column, int row, int numberOfColumns, int numberOfRows);
void newGame(char *player1, char *player2, int columns, int rows);
void displayBoard(struct Position* board, int width);

#endif //ADSCOURSEWORK_GAMEBOARD_H
