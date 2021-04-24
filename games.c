//
// Games Source File
// Created by lewis on 12/04/2021.
//

#include "games.h"

// Creates game with attributes passed in
void newGame(char *player1, char *player2, int columns, int rows){

    //Create Game default Struct
    Game game = {
            .name1 = player1,
            .name2 = player2,
            .rowSize = rows,
            .columnSize = columns,
            .board = constructLinkedMatrix(rows, columns),
            .pTurn = 1,
            .log = newEntry(NULL, 0, 0),
            .gameType = 0,
            .step = 0
    };

    // Go to player's move controller function (ie start game)
    moveController(&game);

};

// Toggles Game Objects Player's Turn Attribute
void togglePlayer(Game* game) {
    if (game->pTurn == 1) {
        game->pTurn = 2;
    } else {
        game->pTurn = 1;
    }
}

// Plan for un/redo would be check user input over 100 and user 101 102... as other options.
int moveController(Game* game){

    // Initialise current player
    char *currentPlayer = "";

    //Loop through player move cycle until a win condition is met
    while (!checkWinConditions(game)) {

        //Set CurrentPlayer Variable Dependant on playerTurn Game Attribute
        if (game->pTurn == 1) {currentPlayer = game->name1;} else {currentPlayer = game->name2;}

        // Heading for Game Board Display
        printf("\n-----Game Board's Current State-----\n\n");
        displayBoard(game->board, game->columnSize);

        //Show Current Player and Show Options
        printf("\nCurrent player is %s!\nPlease enter a column (or 101 to enter Analysis Mode): ", currentPlayer);

        // Get Option from User
        int selection;
        scanf("%d",&selection);

        // Analysis Mode Option Check
        if(selection == 101) {analysisMode(game); return 0;}

        //Validate is valid then insert coin and toggle current player id
        if (isInRange(1,game->columnSize,selection)){

            // Only Toggle Player if Valid Move
            if (!insertCoin(game, selection, game->pTurn)){
                togglePlayer(game);
            }

        } else {printf("\n\nInvalid choice! Try Again!\t");} //Invalid Option Chosen
    }

    // Display Winner and Game Board
    char *winner;
    printf("\n------------------Winner!------------------\n\n");
    displayBoard(game->board, game->columnSize);

    // Get Winners Name
    if (game->winner == 1) {winner = game->name1;} else {winner = game->name2;}

    printf("Congratulations to %s for winning!\n", winner);

    // Next Steps Menu
    int winMenu = 101;
    while(!isInRange(1,3,winMenu)||(winMenu!=101)){
        printf("\nMenu Options: \n1. Save Game and Quit to Menu\n2. Quit to Menu (No Save)\n3. Review Game (Enter Analysis Mode)\n\nChoice:", currentPlayer);
        scanf("%d",&winMenu);

        // Initialise Game Name
        char *gameName = "";

        // Save Log to File
        if (winMenu==1) {
            printf("\nPlease enter a name to identify this game (max 20 characters):");
            scanf("%20s",gameName);

            saveGameLog(*game,gameName);
            menu(); return 0;
        }

        // Return to Menu
        if(winMenu==2){ menu(); return 0;}

        // Enter Analysis Mode
        if (winMenu==3){analysisMode(game); return 0;}

    }

    return 0;
}

int analysisMode(Game* game){

    // Initialise local variables
    struct Entry* log = game->log;
    struct Entry* logCount = log;
    int noOfSteps = 0;

    // Create Board Struct
    struct Position* board;

    //Count number of entries in the log
    while(logCount->next!=NULL) {
        noOfSteps++;
        logCount = logCount->next;
    }

    // Loop through all steps in log
    while(1) {

        log = game->log;
        int stepCounter = game->step;
        board = constructLinkedMatrix(game->rowSize, game->columnSize);

        // Reconstruct board positions at step
        for (int i=0; i<stepCounter+1; i++) {
            if (log!=NULL) {
                reinsertCoin(board, log->move, log->pTurn);
                log = log->next;
            }
        }

        // Pretty Analysis Mode Ascii Text
        printf("\n  ___                   ___  \n"
               " (o o)                 (o o) \n"
               "(  V  ) Analysis Mode (  V  )\n"
               "--m-m-------------------m-m--\n\n");

        // Show Current Board
        displayBoard(board, game->columnSize);

        // Display current player
        printf("Player Turn: %d\n",game->pTurn);

        // Show Analysis Menu and get Choice
        printf("\nAnalysis Menu:\n0. Continue from this point\n1. Undo Move\n2. Redo Next Move\n3. Jump to End (Last Logged Move)\n\nOption: ");
        int analysisMenu;
        scanf("%d",&analysisMenu);

         //If Undo Move Option
        if(analysisMenu == 1 && !(game->step-1 < 0)){
            game->step--;
            if (game->pTurn==1) {game->pTurn=2;}
            else if (game->pTurn==2) {game->pTurn=1;}
        } else if (analysisMenu == 2 && !(game->step+1 > noOfSteps)) {  // Redo move option
            game->step++;
            if (game->pTurn==1) {game->pTurn=2;}
            else if (game->pTurn==2) {game->pTurn=1;}
        } else if (analysisMenu == 0) { // Continue from here Option
            // Update game structs board
            game->board = board;
            //Go back to moveController i.e resume the game
            moveController(game);
            return 0;
        } else if (analysisMenu == 3){ // Move to end of Log
            while(!(game->step+1 > noOfSteps)) { game->step++; if (game->pTurn==1) {game->pTurn=2;} else if (game->pTurn==2) {game->pTurn=1;} }
        } else {
            // Catch when user selects invalid analysis menu option
            printf("\n !! You have reached the start and/or end of the current logged game !!");
        }

    }
}

void saveGameLog(Game game, char* gameName){

    //Initialise and open file
    FILE *fp;
    fp = fopen(GAMEDATAFILE, "a+");

    // Append Data (excluding logs)
    fprintf(fp, "\n%s;%i;%i;%i;%s;%s;",gameName,game.gameType,game.columnSize,game.rowSize,game.name1,game.name2);

    // Print Log to File
    struct Entry* log = game.log;
    char *logStr = "";
    while(log->next!=NULL){
        if (log->move == 0){}
        else if (log->next != NULL){
            fprintf(fp,"%i,",log->move);
        }
        log = log->next;
    }
    //Write last line (different as excluding comma) then close the file.
    fprintf(fp,"%i",log->move);
    fclose(fp);
}

// Create New Entry Structure
struct Entry* newEntry(struct Entry* log, int move, int pTurn) {
    //Assuming log is not empty means valid game
    if (log!=NULL) {

        // Loop through all log entries
        while (log->next!=NULL){
            log = log->next;
        }
        //Create Entry with given attributes
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
// Special copy of insertCoin function with no log update and takes board input rather than game
void reinsertCoin(struct Position* board, int column, int player){

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

//Initialises a position to default values
struct Position* initPosition(){
    struct Position* pos = (struct Position *) malloc(sizeof(struct Position));
    pos->valid = false;
    pos->right = NULL;
    pos->down = NULL;
    pos->left = NULL;
    pos->up = NULL;
    pos->takenBy = 0;
    return pos;
}

// Functions for creating board matrix
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

    // Link Up and Left Pointers
    linkUpLeft(mainHead, row, column);

    return mainHead;
}
//Adds Up and Left Pointers to board
void linkUpLeft(struct Position* board, int row, int column){

    struct Position *pointer, *rowPointer, *colPointer;
    pointer = board;
    colPointer = board;
    rowPointer = board;

    // Loop through each column
    for (int colCounter = 0; colCounter <= column; colCounter++) {

        //pointer = colPointer;

        // Loop Through each row of current column
        for (int rowCounter = 0; rowCounter <= row; rowCounter++) {
            // Set Pointer to the rowPointer
            pointer = rowPointer;

            // if pointer's down is not null,
            if (pointer->down != NULL) {
                pointer->down->up = pointer;
            }

            if (pointer->right != NULL) {
                pointer->right->left = pointer;
            }

            if (rowPointer->down != NULL) {rowPointer = rowPointer->down;}
        }
        if (colPointer->right != NULL) {rowPointer = colPointer->right; colPointer = colPointer->right;}
    }
}

//Displays Board - Requires knowledge of numberOfColumns
void displayBoard(struct Position* board, int width)
{
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
// Inserts coin at selected position by given player into the gameboard
int insertCoin(Game* game, int column, int player){

    // Initialise board pointer
    struct Position* board = game->board;

    //Move 'right' to the correct column
    for (int counter=0; counter<column-1; counter++){
        board = board->right;
    }

    //Check Column Not Full
    if(board->takenBy!=0){return 1;}

    // While not at bottom of grid
    while(board->down!=NULL && board->down->takenBy==0) {
        // Move down
        board = board->down;
    }
    //Set Taken By
    board->takenBy = player;

    // Add move to game log
    newEntry(game->log, column, player);
    game->step++;

    return 0;
}

// All Win Conditions
int checkWinConditions(Game* game){
    if (checkVerticalWinCondition(game) || checkHorizontalWinCondition(game) || checkDiagonalWinConditionNeg(game) || checkDiagonalWinConditionPos(game)) {
        return 1;
    }
    return 0;
}
int checkVerticalWinCondition(Game* game){

    // Initialise pointer and column pointer to first position on the game board
    struct Position *pointer = game->board, *columnPointer = game->board;

    // Loop through each of the Columns of the game board
    for (int colCounter = 0; colCounter <= game->columnSize; colCounter++) {

        // Set consecutive counters to zero
        int cons1 = 0, cons2 = 0;

        // Loop through each of the rows (ie down the column)
        for (int rowCounter = 0; rowCounter <= game->rowSize; rowCounter++) {

            // Check for Null pointer
            if (pointer!=NULL) {

                // Skip other checks if position has not been taken by a player
                if (pointer->takenBy == 0) {}

                    // Else if position is taken by player 1, reset player2's consecutive position counter, and add to player 1's
                else if (pointer->takenBy == 1) {
                    cons1++;
                    cons2 = 0;
                    // Check if found four consecutive 1's
                    if (cons1 >= 4){game->winner = 1; return 1;}
                } else {
                    // Else position must be taken by player 2, reset player1's consecutive position counter, and add to player 2's
                    cons2++;
                    cons1 = 0;
                    // Check if found four consecutive 2's
                    if (cons2 >= 4){game->winner = 2; return 1;}
                }
                // Move pointer down the board
                pointer = pointer->down;
            }
        }

        // See if there is another column to be checked, if move column pointer to new column, set pointer to same position
        if (columnPointer->right != NULL) {
            columnPointer = columnPointer->right;
            pointer = columnPointer;
        }
    }

    // Vertical win condition not met, return false
    return 0;

}
int checkHorizontalWinCondition(Game* game){

    // Initialise pointer and row pointer to first position on the game board
    struct Position *pointer = game->board, *rowPointer = game->board;

    // Loop through each of the Rows of the game board
    for (int rowCounter = 0; rowCounter <= game->rowSize; rowCounter++) {

        // Set consecutive counters to zero
        int cons1 = 0, cons2 = 0;

        // Loop through each of the columns (ie across the rows)
        for (int colCounter = 0; colCounter <= game->columnSize; colCounter++) {

            // Check for Null pointer
            if (pointer!=NULL) {

                // Skip other checks if position has not been taken by a player
                if (pointer->takenBy == 0) {}

                    // Else if position is taken by player 1, reset player2's consecutive position counter, and add to player 1's
                else if (pointer->takenBy == 1) {
                    cons1++;
                    cons2 = 0;
                    // Check if found four consecutive 1's
                    if (cons1 >= 4){game->winner = 1; return 1;}

                } else {
                    // Else position must be taken by player 2, reset player1's consecutive position counter, and add to player 2's
                    cons2++;
                    cons1 = 0;
                    // Check if found four consecutive 2's
                    if (cons2 >= 4){game->winner = 2; return 1;}
                }
                // Move pointer across the board
                pointer = pointer->right;
            }
        }

        // See if there is another row to be checked, if move row pointer to new row, set pointer to same position
        if (rowPointer->down != NULL) {
            rowPointer = rowPointer->down;
            pointer = rowPointer;
        }
    }

    // Horizontal win condition not met, return false
    return 0;

}
int checkDiagonalWinConditionNeg(Game* game){

// Initialise pointer and column pointer to first position on the game board
    struct Position *pointer = game->board, *columnPointer = game->board;

    // Loop through each of the Columns of the game board
    for (int colCounter = 0; colCounter <= game->columnSize; colCounter++) {

        // Set consecutive counters to zero
        int cons1 = 0, cons2 = 0;

        // Loop through each of the rows (ie down the column)
        for (int rowCounter = 0; rowCounter <= game->rowSize-1; rowCounter++) {

            struct Position* tmpPointer = pointer;

            // Loop while tmpPointer is not Null
            while (tmpPointer!=NULL) {

                // Skip other checks (and break loop) if position has not been taken by a player
                if (tmpPointer->takenBy == 0) {break;}

                    // Else if position is taken by player 1, reset player2's consecutive position counter, and add to player 1's
                else if (tmpPointer->takenBy == 1) {
                    cons1++;
                    cons2 = 0;
                    // Check if found four consecutive 1's
                    if (cons1 >= 4){game->winner = 1; return 1;}
                } else {
                    // Else position must be taken by player 2, reset player1's consecutive position counter, and add to player 2's
                    cons2++;
                    cons1 = 0;
                    // Check if found four consecutive 2's
                    if (cons2 >= 4){game->winner = 2; return 1;}
                }
                // Move pointer diagonally down the board
                if (tmpPointer->down!=NULL && tmpPointer->right!=NULL) {
                    tmpPointer = tmpPointer->down->right;
                } else {
                    break;
                }

            }
            // Reset consecutive 1 and 2's as next position has been reached
            cons1 = cons2 = 0;
            // Check pointer is not null else break loop
            if (pointer!=NULL) {
                pointer = pointer->down;
            } else {
                break;
            }
        }

        // See if there is another column to be checked, if move column pointer to new column, set pointer to same position
        if (columnPointer->right != NULL) {
            columnPointer = columnPointer->right;
            pointer = columnPointer;
        }
    }

    // Negative Horizontal win condition not met, return false
    return 0;
}
int checkDiagonalWinConditionPos(Game* game){

// Initialise pointer and column pointer to first position on the game board
    struct Position *pointer = game->board, *columnPointer = game->board;

    // Move pointer to bottom of column
    while( pointer->down != NULL){
        pointer = pointer->down;
    }

    // Loop through each of the Columns of the game board
    for (int colCounter = 0; colCounter <= game->columnSize; colCounter++) {

        // Set consecutive counters to zero
        int cons1 = 0, cons2 = 0;

        // Loop through each of the rows (ie down the column)
        for (int rowCounter = 0; rowCounter <= game->rowSize-1; rowCounter++) {

            struct Position* tmpPointer = pointer;

            // Loop while tmpPointer is not Null
            while (tmpPointer!=NULL) {

                // Skip other checks (and break loop) if position has not been taken by a player
                if (tmpPointer->takenBy == 0) {break;}

                    // Else if position is taken by player 1, reset player2's consecutive position counter, and add to player 1's
                else if (tmpPointer->takenBy == 1) {
                    cons1++;
                    cons2 = 0;
                    // Check if found four consecutive 1's
                    if (cons1 >= 4){game->winner = 1; return 1;}
                } else {
                    // Else position must be taken by player 2, reset player1's consecutive position counter, and add to player 2's
                    cons2++;
                    cons1 = 0;
                    // Check if found four consecutive 2's
                    if (cons2 >= 4){game->winner = 2; return 1;}
                }
                // Move pointer up the board
                if (tmpPointer->up!=NULL && tmpPointer->right!=NULL) {
                    tmpPointer = tmpPointer->up->right;
                } else {
                    break;
                }

            }
            // Reset consecutive 1 and 2's and move pointer up as at new Position on board else break loop
            cons1 = cons2 = 0;
            if (pointer!=NULL) {
                pointer = pointer->up;
            } else {
                break;
            }
        }

        // See if there is another column to be checked, if move column pointer to new column, set pointer to same position
        if (columnPointer->right != NULL) {

            //Move to next column
            columnPointer = columnPointer->right;
            pointer = columnPointer;

            // Move pointer to bottom of column
            while( pointer->down != NULL){pointer = pointer->down;}

        }
    }

    // Positive Horizontal win condition not met, return false
    return 0;
}

// Validation
bool isInRange(int lowerLimit, int upperLimit, int no)
{
    // Checks number is in valid range
    return (lowerLimit <= no && no <= upperLimit);
}

// "Press enter key to continue" Function
void awaitInput(){
    printf("(press enter to continue)\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}