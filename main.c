#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char canvas[3][3];
void init();
void play();
void checkWinner();
void printBoard();
int useGameOver();
const char PLAYER = 'X';
const char AI = 'O';
const char space = ' ';
char winner = ' ';
int plays;
int wins;

int main() {
    init();
    do {
        printBoard();
        play();
        checkWinner();
    } while (winner == space);
    useGameOver();
    return 0;
}

void init () {
    plays++;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            canvas[i][j] = space;
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c \n",canvas[0][0],canvas[0][1],canvas[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n",canvas[1][0],canvas[1][1],canvas[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n",canvas[2][0],canvas[2][1],canvas[2][2]);
}

void play () {
    int clientX;
    int clientY;
    // user play
    printf("\rChoose your spot across the board [left to right] (1-3):");
    scanf("%d", &clientX);
    clientX--;
    printf("\rChoose your spot along the board [top to bottom] (1-3):");
    scanf("%d", &clientY);
    clientY--;
    if (canvas[clientY][clientX]==space) {
        canvas[clientY][clientX] = PLAYER;
    } else {
        printf("Invalid Spot\n");
    }

    int aiX;
    int aiY;
    // AI play
    srand(time(0));
    aiX = rand() % 3;
    aiY = rand() % 3;
    int stop=0;
    if (canvas[aiY][aiX]==space) {
        canvas[aiY][aiX] = AI;
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (canvas[i][j]==space) {
                    canvas[i][j]=AI;
                    stop=1;
                    break;
                }
                if (stop) {
                    break;
                }
            }
            if (stop) {
               break;
            }
        }
        
    }
}

void checkWinner(){
    if (canvas[0][0]==canvas[0][1]&&canvas[0][0]==canvas[0][2]) {
        winner = canvas[0][0];
    }
    else if (canvas[1][0] == canvas[1][1] && canvas[1][0] == canvas[1][2]){
        winner = canvas[1][0];
    } else if (canvas[2][0] == canvas[2][1] && canvas[2][0] == canvas[2][2]) {
        winner = canvas[2][0];
    } else if (canvas[0][0] == canvas[1][1] && canvas[0][0] == canvas[2][2]) {
        winner = canvas[0][0];
    } else if (canvas[0][2] == canvas[1][1] && canvas[0][2] == canvas[2][0]) {
        winner = canvas[0][2];
    }else if (canvas[0][0] == canvas[1][0] && canvas[0][0] == canvas[2][0]){
        winner = canvas[0][0];
    }else if (canvas[0][1] == canvas[1][1] && canvas[0][1] == canvas[2][1]){
        winner = canvas[0][1];
    }else if (canvas[0][2] == canvas[1][2] && canvas[0][2] == canvas[2][2]){
        winner = canvas[0][2];
    } else {
        winner = space;
    }
    // printf("\n winner: %c\n", winner);
}

int useGameOver () {
    printBoard();
    if (winner==PLAYER) {
        printf("\nYOU WON :)");
        wins++;
    }
    else if (winner == AI) {
        printf("\nYOU LOOSE :(");
    } else if (winner == space) {
        printf("\nIT'S A TIE :|");
    }
    printf("\nDo you want to play again (y/n)?");
    char resp[3];
    scanf("%s",&resp);
    if (tolower(resp[0])=='y') {
        printf("\nOkay... Starting new game\n");
        return main();
    } else {
        printf("\nThanks for playing :)");
        printf("\nYou WON %d of %d plays %s", wins, plays, !wins ? ":(" : ":)");
        exit(0);
    }
    return 0;
}