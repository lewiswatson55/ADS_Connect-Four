//
// Game Board
// Created by lewis on 12/04/2021.
// https://www.geeksforgeeks.org/construct-linked-list-2d-matrix/
//

#include "games.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_GRID_SIZE 10

void newGame(char *player1, char *player2, int columns, int rows){

    //Create Game Struct
    Game game = {
            .name1 = player1,
            .name2 = player2,
            .rowSize = rows,
            .columnSize = columns,
            .board = constructLinkedMatrix(rows, columns),
            .pTurn = 1,
            .log = newEntry(NULL, 0, 0),
            .gameEnded = false,
            .gameType = 0
    };

    moveController(game);

};

void moveController(Game game){

    printf("-----Game Board's Current State-----\n\n");
    displayBoard(game.board, game.columnSize);

    char selection[10];
    printf("\nCurrent player is %s!\nPlease select a column: ", game.name1);
    fgets(selection, 8, stdin);
    printf("Column %s chosen...", selection);


}

//nofcolumns = rows
struct Position* createBoard(int row, int column, int numberOfColumns, int numberOfRows){

    count++;

    // Ensure current row or column is not outwith board size.
    if (row  > numberOfColumns - 1 || column > numberOfRows - 1)
        return NULL;

    valid++;

    struct Position *temp;

    temp = (struct Position *) malloc(sizeof(struct Position));
    //temp->takenBy = 0;
    temp->takenBy = 0;
    temp->valid = true;
    temp->right = createBoard(row+1, column, numberOfColumns, numberOfRows);
    temp->down = createBoard(row, column+1, numberOfColumns, numberOfRows);
    return temp;
};

struct Entry* newEntry(struct Entry* log, int move, int pTurn) {
    if (log!=NULL) {

        while (log->next!=NULL){
            log = log->next;
        }
        struct Entry* entry = (struct Entry *) malloc(sizeof(struct Entry));
        entry->prev = log;
        entry->next = NULL;
        entry->move = move;
        entry->pTurn = pTurn;

        log->next = entry;

    } else {
        // Only to be ran when initialising a new log
        struct Entry* log = (struct Entry *) malloc(sizeof(struct Entry));
        log->prev = NULL;
        log->next = NULL;
        log->move = move;
        log->pTurn = pTurn;
        return log;
    }

    return log;
}

//Initialises a position to default values
struct Position* initPosition(){
    struct Position* pos = (struct Position *) malloc(sizeof(struct Position));
    pos->valid = false;
    pos->right = NULL;
    pos->down = NULL;
    pos->takenBy = 0;
    return pos;
}

//Method to perform a deep copy of a position
struct Position* deepCopyPosition(struct Position* to, struct Position* from){
    if (from!=NULL && to!=NULL) {
        to->valid = from->valid;
        to->right = from->right;
        to->down = from->down;
        to->takenBy = from->takenBy;
        return to;
    }
    //If null passed in on either to or from, just create new position with default values.
    struct Position* other = initPosition();
    return other;
}

struct Position* constructLinkedMatrix(int row, int column) {

    struct Position* head[MAX_GRID_SIZE];
    struct Position *mainHead;
    struct Position *rightTemp, *tmpHead, *newPtr;

    mainHead = NULL;
    tmpHead = initPosition();
    newPtr = initPosition();
    rightTemp = initPosition();

    //Set New Ptr to blank Position
    newPtr->valid = true;
    newPtr->takenBy = 0;

    for(int i=0; i<row; i++){

        head[i] = NULL;

        //J not used as just for the looping count (could be used if populating from 2d array ie arr[i][j])
        for(int j=0; j<column; j++){

            tmpHead->takenBy = 0;
            tmpHead->valid = false;
            newPtr = initPosition();

            //Initialise Main head Variable with tmpHead variable
            if (!mainHead) {
                mainHead = newPtr;
            }

            //if head i not valid, initialise
            if (!head[i]) {
                head[i] = newPtr;
            } else {
                  // if initialised, position is along column so
                  rightTemp->right = newPtr;
            }
            rightTemp = newPtr;
        }
    }

    //Set Links for down
    for (int i=0; i<row-1;i++) {

        struct Position* temp1 = head[i], *temp2 = head[i+1];
        while(temp1 && temp2){
            temp1->down = temp2;
            temp1 = temp1->right;
            temp2 = temp2->right;
        }
    }
    return mainHead;
}

void insertCoin(struct Position* board, int column, int player){

    //Move 'right' to the correct column
    for (int counter=0; counter<column-1; counter++){
        board = board->right;
    }

    // While not at bottom of grid
    while(board->down!=NULL && board->down->takenBy==0) {
        board = board->down;
    }
    board->takenBy = player;
}

void displayBoard(struct Position* board, int width)
{
    // Clear Screen
    //system("cls");

    // Create Row Pointer
    struct Position* row;

    // Create Column Pointer
    struct Position* column = board;

    // UI: Display Column Labels
    printf("  ");
    for (int i = 1; i<=width; i++) {printf("  %d   ",i);}
    printf("\n");

    // Loop until current column is NULL
    while (column != NULL) {
        row = column;

        // UI: Side of Board
        printf("||");

        // loop till node->right is not NULL
        while (row != NULL) {
            printf("  %d  |", row->takenBy);
            row = row->right;
        }
        printf("|\n");
        column = column->down;
    }
}
