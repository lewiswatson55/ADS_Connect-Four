//Game Header File
#include "games.h"

// Entry Point
int main(int argc, char **argv){menu();}

// Menu Handler
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

// Start Normal Game
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

// Start CPU Game
void cpuGame(){
    menu();
}

// Open Load Games Menu
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

// Loads selected game into Analysis Mode
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
        fileCount++;
    }

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