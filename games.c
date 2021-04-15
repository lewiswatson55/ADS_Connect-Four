//
// Game Board
// Created by lewis on 12/04/2021.
// https://www.geeksforgeeks.org/construct-linked-list-2d-matrix/
//

#include "games.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


    printf("0");
    // Ensure current row or column is not outwith board size.
    if (row  > numberOfColumns - 1 || column > numberOfRows - 1)
        return NULL;

    printf("1");
    struct Position *temp;

    temp = (struct Position *) malloc(sizeof(struct Position));
    temp->takenBy = 0;
    temp->right = createBoard(row+1, column, numberOfColumns, numberOfRows);
    printf("2");
    temp->down = createBoard(row, column+1, numberOfColumns, numberOfRows);
    //displayBoard(temp, 3);
    return temp;


};

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
