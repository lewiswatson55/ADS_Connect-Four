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
    Game game = {.name1 = player1,
            .name2 = player2,
            .rowSize = rows,
            .columnSize = columns,
            .board = createBoard(0, 0, columns, rows)};

    moveController(game);

};

void moveController(Game game){

    printf("-----Game Board's Current State-----");
    displayBoard(game.board, game.rowSize);

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
    struct Position* other = initPosition();
    return other;
}

struct Position* constructLinkedMatrix(int row, int column) {

    struct Position* head[MAX_GRID_SIZE];
    struct Position *mainHead;

    struct Position *rightTemp, *tmpHead, *newPtr;
//    tmpHead = (struct Position *) malloc(sizeof(struct Position));
//    mainHead = (struct Position *) malloc(sizeof(struct Position));
//    newPtr = (struct Position *) malloc(sizeof(struct Position));
//    rightTemp = (struct Position *) malloc(sizeof(struct Position));
    mainHead = NULL;
    tmpHead = initPosition();
    newPtr = initPosition();
    rightTemp = initPosition();

//    for(int counter=0; counter<MAX_GRID_SIZE; counter++) {
//        head[counter] = (struct Position *) malloc(sizeof(struct Position));
//        head[counter]->valid = false;
//        head[counter]->takenBy = 0;
//          //head[counter] = initPosition();
//    }

    //Set New Ptr to blank Position
    newPtr->valid = true;
    newPtr->takenBy = 0;

    for(int i=0; i<row; i++){

//        head[i] = (struct Position *) malloc(sizeof(struct Position));
//        head[i]->valid = false;
//        head[i]->takenBy = 0;
        //head[i] = initPosition();
        head[i] = NULL;

        //J not used as just for the looping count (could be used if populating from 2d array ie arr[i][j])
        for(int j=0; j<column; j++){

            tmpHead->takenBy = 0;
            tmpHead->valid = false;
            newPtr = initPosition();

            //Initialise Main head Variable with tmpHead variable
            if (!mainHead) {
                //memcpy(&newPtr,&mainHead, sizeof(struct Position *));
                //mainHead = deepCopyPosition(mainHead,newPtr);]
                //newPtr->valid = false;
                mainHead = newPtr;
//                mainHead->takenBy = 0;
//                mainHead->valid = true;
            }

            //if head i not valid, initialise
            if (!head[i]) {

                //memcpy(&newPtr,&head[i], sizeof(struct Position *));
                //head[i] = deepCopyPosition(head[i], newPtr);
                head[i] = newPtr;
                //if (i==0) {head[i] = mainHead;}
//                head[i]->takenBy = 0;
//                head[i]->valid = true;

            } else {
                  // if initialised, position is along column so
                //rightTemp->right = (struct Position *) malloc(sizeof(struct Position));
//                rightTemp->right->takenBy=0;
//                rightTemp->right->valid=true;
                //memcpy(&newPtr,&rightTemp->right, sizeof(struct Position *));
                //rightTemp->right = deepCopyPosition(rightTemp->right, newPtr);
                  rightTemp->right = newPtr;
            }
//            rightTemp = (struct Position *) malloc(sizeof(struct Position));
//            rightTemp->takenBy=0;
//            rightTemp->valid=true;
            rightTemp = newPtr;
            //memcpy(&newPtr,&rightTemp->right, sizeof(struct Position *));
            //rightTemp = deepCopyPosition(rightTemp, newPtr);
        }
    }

    //Set Links for down
    for (int i=0; i<row-1;i++) {

        struct Position* temp1 = head[i], *temp2 = head[i+1];
        while(temp1 && temp2){
//            temp1->down = deepCopyPosition(temp2, temp1->down);
//            temp1 = deepCopyPosition(temp1->right, temp1);
//            temp2 = deepCopyPosition(temp2->right, temp2);
            temp1->down = temp2;
            temp1 = temp1->right;
            temp2 = temp2->right;
        }
    }

    return mainHead;
}

void insertCoin(struct Position* board, int column){

    for (int counter=0; counter<column-1; counter++){
        board = board->right;
        printf("a\n");
    }

    // While not at bottom of grid
    while(board->down!=NULL && board->down->takenBy==0) {
        board = board->down;
    }
    board->takenBy = 1;
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
