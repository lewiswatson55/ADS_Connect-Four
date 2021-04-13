//
// Created by lewis on 13/04/2021.
//

#ifndef ADSCOURSEWORK_GAMEBOARD_H
#define ADSCOURSEWORK_GAMEBOARD_H

struct Position {
    int takenBy;
    struct Position *right, *down;
};

struct Position* createBoard(int column, int row, int numberOfColumns, int numberOfRows);
void displayBoard(struct Position* board);

#endif //ADSCOURSEWORK_GAMEBOARD_H
