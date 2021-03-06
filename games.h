//
// Games Header File
// Created by lewis on 13/04/2021.
//

#ifndef ADSCOURSEWORK_GAMEBOARD_H
#define ADSCOURSEWORK_GAMEBOARD_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 1000
#define MAX_GRID_SIZE 10
//#define GAMEDATAFILE "C:\\Users\\lewis\\CLionProjects\\ADSCoursework\\gamedata.txt"
#define GAMEDATAFILE "./gamedata.txt"

// Global Menu Variable
char menuSelection;


// Data Structures
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
    //struct Entry *prev;
    struct Entry *next;
    int pTurn;
    int move;
};

struct Position {
    int takenBy;
    struct Position *right, *down, *left, *up;
};

// DS Initialisers
struct Position* constructLinkedMatrix(int row, int column);
void linkUpLeft(struct Position* board, int row, int column);

struct Entry* newEntry(struct Entry* log, int move, int pTurn);

// Menu
void menu();
void newGame(int gameType, char *player1, char *player2, int columns, int rows);
void startGame(int gameType);
void loadLog(char line[LINE_LENGTH]);
void loadGames();

// In Game
int moveController(Game* game);
void insertCPU(Game* game);
void displayBoard(struct Position* board, int width);
int insertCoin(Game* game, int column, int player);
void saveGameLog(Game game, char* gameName);

// Validation and Checks
bool isInRange(int lowerLimit, int upperLimit, int no);

int checkWinConditions(Game* game);
int checkVerticalWinCondition(Game* game);
int checkHorizontalWinCondition(Game* game);
int checkDiagonalWinConditionNeg(Game* game);
int checkDiagonalWinConditionPos(Game* game);

void awaitInput();

// Reconstructing and Analysis Mode
int analysisMode(Game* game);
void reinsertCoin(struct Position* board, int column, int player);
void reconstructBoard(Game* game);

#endif //ADSCOURSEWORK_GAMEBOARD_H
