//
// Game Board
// Created by lewis on 12/04/2021.
// https://www.geeksforgeeks.org/construct-linked-list-2d-matrix/
//

#include "games.h"
#include <stdio.h>
#include <stdlib.h>

struct Position* createBoard(int column, int row, int numberOfColumns, int numberOfRows){

    // Ensure current row or column is not outwith board size.
    if (row  > numberOfRows - 1 || column > numberOfColumns - 1)
        return NULL;

    struct Position *temp;

    temp = (struct Position *) malloc(sizeof(struct Position));
    temp->takenBy = 0;
    temp->right = createBoard(column, row+1, numberOfColumns, numberOfRows);
    temp->down = createBoard(column+1, row, numberOfColumns, numberOfRows);
    return temp;

};

void displayBoard(struct Position* board)
{
    // Clear Screen
    system("cls");

    // Create Row Pointer
    struct Position* row;

    // Create Column Pointer
    struct Position* column = board;

    // UI: Column Labels (33_'s)
    printf("_________________________________\n");

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
