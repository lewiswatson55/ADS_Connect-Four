//
// Created by lewis on 13/04/2021.
//

#ifndef ADSCOURSEWORK_GAMEBOARD_H
#define ADSCOURSEWORK_GAMEBOARD_H

#include <stdbool.h>
#define MAX_GRID_SIZE 10

int count, valid;

typedef struct {
    char *name1, *name2;
    int rowSize, columnSize;
    int gameType;
    struct Position* board;
    struct Entry *log;
    int pTurn;
    int winner;
    int step;
} Game;

// Log Entry
struct Entry {
    struct Entry *prev;
    struct Entry *next;
    int pTurn;
    int move;
};

//struct node{
//    struct Position * data;
//    struct node * link;
//};

struct Position {
    bool valid;
    int takenBy;
    struct Position *right, *down, *left, *up;
};

struct Position* createBoard(int column, int row, int numberOfColumns, int numberOfRows);
struct Entry* newEntry(struct Entry* log, int move, int pTurn);
void newGame(char *player1, char *player2, int columns, int rows);
void displayBoard(struct Position* board, int width);
int moveController(Game* game);
void insertCoin(Game* game, int column, int player);
int checkWinConditions(Game* game);
int checkVerticalWinCondition(Game* game);
int checkHorizontalWinCondition(Game* game);
int checkDiagonalWinConditionNeg(Game* game);
int checkDiagonalWinConditionPos(Game* game);
void gameController();
void player1Move(),player2Move();
void gravityMove(); //Animate dropping?

void linkUpLeft(struct Position* board, int row, int column);

int analysisMode(Game* game);

struct Position* constructLinkedMatrix(int row, int column);
void reconstructBoard(Game* game);
void reinsertCoin(struct Position* board, int column, int player);

#endif //ADSCOURSEWORK_GAMEBOARD_H
