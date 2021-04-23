#include <stdio.h>

#define LINE_LENGTH 1000
#define NAME_SIZE 25
#define GAMEDATAFILE "C:\\Users\\lewis\\CLionProjects\\ADSCoursework\\gamedata.txt"

//Game Header File
#include "games.h"
#include <stdlib.h>

char menuSelection;

void startGame();
void loadLog(char line[LINE_LENGTH]);
void loadGames();
void otherOption();

void menu(){

    printf("\nWelcome to Connect Four - CLI Edition!\n\nPlease select from the menu then press enter...\n\n1. Start Game\n2. Other Option\n0. Exit\nChoice:  ");
    fgets(&menuSelection,8,stdin);

    switch (menuSelection) {
        case '0':
            return;
            break;
        case '1':
            startGame();
            break;
        case '2':
            otherOption();
            break;

        default:
            printf("Invalid Choice... %c", menuSelection);
            break;
    }
}


int main(int argc, char **argv)
{
    //menu();
    //newGame("Lewis", "Kate", 7, 6);



    //struct Position *board = createBoard(0,0,3,3);
    //struct Position *board = constructLinkedMatrix(10,10);

    //struct Entry* loggyboi = newEntry(NULL, 0, 0);
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

//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 6, 2);
//    insertCoin(&game, 4, 1);
//    insertCoin(&game, 3, 1);
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

    loadGames();

    return 0;
}

void startGame(){
    printf("\nStart Game\n");
}

void otherOption(){
    printf("\nOther Option\n");
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