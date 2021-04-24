#include <stdio.h>

#define LINE_LENGTH 1000

//Game Header File
#include "games.h"
#include <stdlib.h>

void startGame();
void loadLog(char line[LINE_LENGTH]);
void loadGames();

void menu(){

    // Clear Command Prompt - Window's Exclusive, could use preprocessor to change this depending on OS however, this has not been implemented.
    //system("cls");

    printf("\nWelcome to Connect Four - CLI Edition!\n\nPlease select from the menu then press enter...\n\n"
           "1. New Game\n2. New Game (Against CPU)\n3. Playback Game (Analysis Mode)\n0. Exit\n\nChoice:  ");
    fgets(&menuSelection,8,stdin);

    switch (menuSelection) {
        case '0': // Exit
            return;
            break;
        case '1': // Normal Game
            startGame();
            break;
        case '2': // CPU Game
            //cpuGame();
            break;

        case '3': // Analysis Mode Replay
            loadGames();
            break;

        default:
            printf("\n\nInvalid Choice... %c\n", menuSelection);
            menu();
            break;
    }
}


int main(int argc, char **argv)
{
    //awaitInput();
    menu();
    //newGame("Lewis", "Kate", 7, 6);



    //struct Position *board = createBoard(0,0,3,3);
    //struct Position *board = constructLinkedMatrix(10,10);

//    struct Entry* loggyboi = newEntry(NULL, 0, 0);
//    newEntry(loggyboi, 1, 1);
//    newEntry(loggyboi, 1, 2);

    //Create Game Struct
//    Game game = {
//            .name1 = "player1",
//            .name2 = "player2",
//            .rowSize = 7,
//            .columnSize = 6,
//            .board = constructLinkedMatrix(7, 6),
//            .pTurn = 1,
//            .log = loggyboi,
//            .gameType = 0,
//            .step = 0
//
//    };
//
//    insertCoin(&game, 6, 1);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 4, 1);
//    insertCoin(&game, 3, 2);
//
//    analysisMode(&game);

    //reinsertCoin(game.board, 1, 2);
//    displayBoard(game.board,6);
//    reconstructBoard(&game);
//    displayBoard(game.board,6);
//    insertCoin(&game, 2, 2);
//    insertCoin(&game, 2, 1);
//    insertCoin(&game, 3, 1);
//    insertCoin(&game, 3, 1);
//    insertCoin(&game, 3, 1);
//    insertCoin(&game, 4, 1);
//    insertCoin(&game, 4, 2);
//    insertCoin(&game, 4, 2);
//    insertCoin(&game, 4, 1);
//    insertCoin(&game, 5, 1);
//    insertCoin(&game, 5, 1);
//    insertCoin(&game, 5, 2);
//    insertCoin(&game, 5, 2);
//    insertCoin(&game, 5, 1);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 6, 1);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 6, 2);

//    insertCoin(game.board, 6, 2);
//    insertCoin(game.board, 5, 2);
//    insertCoin(game.board, 5, 1);
//    insertCoin(game.board, 4, 1);
//    insertCoin(game.board, 4, 1);
//    insertCoin(game.board, 4, 1);
//    insertCoin(game.board, 3, 1);
//    insertCoin(game.board, 3, 2);
//    insertCoin(game.board, 3, 2);
//    insertCoin(game.board, 3, 2); //Toggle
//    insertCoin(game.board, 2, 1);
//    insertCoin(game.board, 2, 1);
//    insertCoin(game.board, 2, 2);
//    insertCoin(game.board, 2, 2);
//    insertCoin(game.board, 2, 1);
//    insertCoin(game.board, 1, 2);
//    insertCoin(game.board, 1, 2);
//    insertCoin(game.board, 1, 1);
//    insertCoin(game.board, 1, 2);
//    insertCoin(game.board, 1, 2);
//    insertCoin(game.board, 1, 2);

//    displayBoard(game.board, 6);
//
//    if (checkWinConditions(&game)) {
//        printf("WINNER");
//    }

//    if (checkDiagonalWinConditionNeg(&game)) {
//        printf("WINNER");
//    }

//    printf("\n\nCalls: %d\nValid: %d\n\n\n", count, valid);

//    struct Entry * log = newEntry(NULL, 0, 0);
//    newEntry(log, 1,1);
//    newEntry(log, 2,2);
//    newEntry(log, 1,1);
//    newEntry(log, 2,2);
//    newEntry(log, 1,1);
//    newEntry(log, 2,2);

    //loadGames();

    //saveGameLog(game, "Apples");

    return 0;
}

void startGame(){

    // Initialise Variables
    char playerOne[20], playerTwo[20];
    int boardSize;

    printf("\nEnter Player One's Name (Max 20 Characters):");
    scanf("%s",playerOne);

    printf("\nEnter Player Two's Name (Max 20 Characters):");
    scanf("%s",playerTwo);

    // Show Menu Options
    printf("\n\n\nPlease select a Game Type:\n\n1. Standard Game (7x6 Board)\n2. Mini Game (4x4)\n3. Massive Game (10x10)\n4. Custom Game (Variable Board Size/Shape)\n");

    // Show Game List Menu and get Choice
    printf("\nGame Choice:");
    scanf("%d",&boardSize);

    // Validate Input
    if(!isInRange(1,4,boardSize)){startGame();}

    else {
        if(boardSize==1){newGame(playerOne, playerTwo,7,6);} //Normal Game
        else if(boardSize==2){newGame(playerOne,playerTwo,4,4);} //Mini Game
        else if(boardSize==3){newGame(playerOne,playerTwo,10,10);} //Big Game
        else if(boardSize==4){

            // Initialise Variables
            int selectedCol;
            int selectedRow;

            //Get Cols
            printf("\nHow many columns? (4-10):");
            scanf("%d",&selectedCol);

            //Validate
            if (!isInRange(4,10,selectedCol)){menu();}

            //Get Rows
            printf("\nHow many rows? (2-10):");
            scanf("%d",&selectedRow);

            //Validate
            if (!isInRange(2,10,selectedRow)){menu();}

            //Start the Game
            newGame(playerOne,playerTwo,selectedCol,selectedRow);

        }
    }


}

void cpuGame(){
    menu();
}

void loadGames(){

    // File Pointer
    FILE *fptr, *fptr2;
    fptr = fopen(GAMEDATAFILE, "r");
    fptr2 = fopen(GAMEDATAFILE, "r");
    char line[LINE_LENGTH], line2[LINE_LENGTH];
    int gamesCount = 0;
    char* gameName = "";

    printf("\nPlease select which of the saved games you would like to replay...\n\nAvailable Games:\n");

    while(fgets(line,LINE_LENGTH,fptr) != NULL) {

        gamesCount++;
        gameName[0] = '\0';

        for (int i = 0; i < strlen(line); i++) {
            while (line[i] != ';') {
                sprintf(gameName,"%s%c",gameName,line[i]);
                break;
            }
            if (line[i]==';'){break;}
        }

        printf("Game %d. %s\n",gamesCount, gameName);

    }

    if (gamesCount!=0){
        // Load Selected Line
        int gameLoadChoice = 0;
        int lineCounter = 0;

        // Show Game List Menu and get Choice
        printf("\nGame Choice:");
        scanf("%d",&gameLoadChoice);

        while(fgets(line,LINE_LENGTH,fptr2) != NULL) {


            if(isInRange(1,gamesCount,gameLoadChoice)) {
                lineCounter++;
                if (lineCounter==gameLoadChoice){loadLog(line); break;}
            } else {printf("Invalid choice!! Try again..."); loadGames(); return;}
        }
    } else {
        // No games in game data file...
        printf("No games were found... Returning to Main Menu!");
    }



}

void loadLog(char line[LINE_LENGTH]) {

    int *columnSize, *rowSize;
    char *player1, *player2;
    int *gameType, fileCount = 0;
    struct Entry* log = newEntry(NULL,0,0);

    player1 = player2 = NULL;


    //Split line into parts, loop until part variable (p) is null
    for (char *p = strtok(line,";"); p != NULL; p = strtok(NULL, ";"))
    {
        if (fileCount==1){char *ptr; int i = strtol(p, &ptr, 10); gameType = &i;}
        else if (fileCount==2){char *ptr; int i = strtol(p, &ptr, 10); columnSize = &i;}
        else if (fileCount==3){char *ptr; int i = strtol(p, &ptr, 10); rowSize = &i;}
        else if (fileCount==4){
            player1 = p;
        } else if (fileCount == 5){player2 = p;}
        else if (fileCount==6) {
            int pTurn = 1;
            for (char *c = strtok(p,","); c != NULL; c = strtok(NULL, ",")) {
                char *ptr; int i = strtol(c, &ptr, 10);
                newEntry(log,i,pTurn);
                if(pTurn==1){pTurn=2;}else{pTurn=1;}
            }
        }
        //printf("%s\n", p);
        fileCount++;
    }

    //printf("\n\nPlayer 1: %s\nPlayer 2: %s\nColumn:Row: %d:%d\nLog: Maybe?",player1,player2,*columnSize,*rowSize);
    //printf("\n\n%s",columnSize);

    //Create Game Struct
    Game game = {
            .name1 = player1,
            .name2 = player2,
            .rowSize = *rowSize,
            .columnSize = *columnSize,
            .board = constructLinkedMatrix(*rowSize, *columnSize),
            .pTurn = 1,
            .log = log,
            .gameType = *gameType,
            .step = 0
    };

    // Enter Analysis Mode
    analysisMode(&game);

}