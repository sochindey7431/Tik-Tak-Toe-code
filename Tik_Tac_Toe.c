#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char board[] = {'0','1','2','3','4','5','6','7','8','9'};

void print_board();
int checkWin();
void saveResult(char p1[], char p2[], char winner[], int p1_score, int p2_score, int draw);
void loadScore(int *p1_score, int *p2_score, int *draw);
void resetBoard();
void playGamePvP(char player1[], char player2[], int *p1_score, int *p2_score, int *draw);
void playGamePvC(char player[], char computer[], int *p1_score, int *p2_score, int *draw);
int getEasyMove();
void showScoreboard(); 

int main()
{
    int p1_score = 0, p2_score = 0, draw = 0;

    loadScore(&p1_score, &p2_score, &draw);

    while(1)
    {
        printf("\n=== TIC TAC TOE MENU ===\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer (Easy)\n");
        printf("3. View Scoreboard\n");  
        printf("4. Exit\n");
        printf("Choose option: ");
        int choice;
        scanf("%d",&choice);

        if(choice == 1)
        {
            char player1[50], player2[50];
            printf("Enter Player 1 Name: "); scanf("%s", player1);
            printf("Enter Player 2 Name: "); scanf("%s", player2);

            playGamePvP(player1, player2, &p1_score, &p2_score, &draw);
        }
        else if(choice == 2)
        {
            char player[50], computer[50];
            printf("Enter Your Name: "); scanf("%s", player);
            strcpy(computer, "Computer");

            playGamePvC(player, computer, &p1_score, &p2_score, &draw);
        }
        else if(choice == 3)
        {
            showScoreboard();  
        }
        else if(choice == 4)
        {
            printf("Final Score:\n");
            printf("%s Wins: %d\n", "Player1", p1_score);
            printf("%s Wins: %d\n", "Player2", p2_score);
            printf("Draws: %d\n", draw);
            break;
        }
        else
        {
            printf("Invalid option! Try again.\n");
        }
    }

    return 0;
}

void playGamePvP(char player1[], char player2[], int *p1_score, int *p2_score, int *draw)
{
    resetBoard();
    print_board();

    int player = 1, input, status = -1;

    while(status == -1)
    {
        printf("\nEnter number (1-9) for %s (Player %d): ",
               (player==1 ? player1 : player2), player);
        scanf("%d", &input);

        if(input < 1 || input > 9){
            printf("INVALID INPUT! Try again.\n");
            continue;
        }

        if(board[input] == 'X' || board[input] == 'O'){
            printf("Position already taken! Try again.\n");
            continue;
        }

        char mark = (player == 1) ? 'X' : 'O';
        board[input] = mark;

        print_board();

        status = checkWin();

        if(status == 1){
            char winner[50];
            strcpy(winner, (player==1 ? player1 : player2));

            if(player == 1) (*p1_score)++;
            else (*p2_score)++;

            printf("\nWinner: %s (Player %d)\n", winner, player);

            saveResult(player1, player2, winner, *p1_score, *p2_score, *draw);
            return;
        }
        else if(status == 0){
            printf("\nMatch Draw!\n");
            (*draw)++;
            saveResult(player1, player2, "DRAW", *p1_score, *p2_score, *draw);
            return;
        }

        player = (player == 1) ? 2 : 1;
    }
}


void playGamePvC(char player[], char computer[], int *p1_score, int *p2_score, int *draw)
{
    resetBoard();
    print_board();

    int playerTurn = 1, input, status = -1;

    while(status == -1)
    {
        if(playerTurn)
        {
            printf("\nEnter number (1-9) for %s: ", player);
            scanf("%d", &input);

            if(input < 1 || input > 9){
                printf("INVALID INPUT! Try again.\n");
                continue;
            }
            if(board[input] == 'X' || board[input] == 'O'){
                printf("Position already taken! Try again.\n");
                continue;
            }
            board[input] = 'X';
        }
        else
        {
            printf("\nComputer is making a move...\n");
            int move = getEasyMove();
            board[move] = 'O';
            printf("Computer chose: %d\n", move);
        }

        print_board();

        status = checkWin();

        if(status == 1){
            if(playerTurn)
            {
                printf("\nWinner: %s\n", player);
                (*p1_score)++;
                saveResult(player, computer, player, *p1_score, *p2_score, *draw);
            }
            else
            {
                printf("\nWinner: %s\n", computer);
                (*p2_score)++;
                saveResult(player, computer, computer, *p1_score, *p2_score, *draw);
            }
            return;
        }
        else if(status == 0){
            printf("\nMatch Draw!\n");
            (*draw)++;
            saveResult(player, computer, "DRAW", *p1_score, *p2_score, *draw);
            return;
        }

        playerTurn = !playerTurn;
    }
}


int getEasyMove()
{
    int freeCells[9], count=0;
    for(int i=1;i<=9;i++)
    {
        if(board[i] != 'X' && board[i] != 'O') freeCells[count++] = i;
    }
    if(count == 0) return -1;

    srand(time(NULL));
    return freeCells[rand()%count];
}


void print_board()
{
    system("cls");

    printf("\n\n==== TIC TAC TOE ====\n\n");
    printf("     |     |   \n");
    printf("  %c  |  %c  | %c \n", board[1],board[2],board[3]);
    printf("_____|_____|_____\n");
    printf("     |     |   \n");
    printf("  %c  |  %c  | %c \n", board[4],board[5],board[6]);
    printf("_____|_____|_____\n");
    printf("     |     |   \n");
    printf("  %c  |  %c  | %c \n", board[7],board[8],board[9]);
    printf("     |     |   \n");
}


void resetBoard()
{
    for(int i=1;i<=9;i++) board[i] = '0' + i;
}


int checkWin()
{
    if(board[1]==board[2] && board[2]==board[3]) return 1;
    if(board[4]==board[5] && board[5]==board[6]) return 1;
    if(board[7]==board[8] && board[8]==board[9]) return 1;

    if(board[1]==board[4] && board[4]==board[7]) return 1;
    if(board[2]==board[5] && board[5]==board[8]) return 1;
    if(board[3]==board[6] && board[6]==board[9]) return 1;

    if(board[1]==board[5] && board[5]==board[9]) return 1;
    if(board[3]==board[5] && board[5]==board[7]) return 1;

    int count = 0;
    for(int i=1; i<=9; i++){
        if(board[i]=='X' || board[i]=='O') count++;
    }

    if(count == 9) return 0;

    return -1;
}


void saveResult(char p1[], char p2[], char winner[], int p1_score, int p2_score, int draw)
{
    FILE *fp = fopen("game_result.txt", "w");
    
    fprintf(fp, "=== Tic Tac Toe Result ===\n");
    fprintf(fp, "Player 1: %s\n", p1);
    fprintf(fp, "Player 2: %s\n", p2);
    fprintf(fp, "Winner : %s\n", winner);

    fprintf(fp, "\n=== SCORE BOARD ===\n");
    fprintf(fp, "Player 1 Wins: %d\n", p1_score);
    fprintf(fp, "Player 2 Wins: %d\n", p2_score);
    fprintf(fp, "Draws : %d\n", draw);

    fclose(fp);

    printf("\nResult and Score saved to game_result.txt\n");
}

void loadScore(int *p1, int *p2, int *dr)
{
    FILE *fp = fopen("game_result.txt", "r");
    if(fp == NULL) return;

    char text[100];

    while(fgets(text, 100, fp)){
        sscanf(text, "Player 1 Wins: %d", p1);
        sscanf(text, "Player 2 Wins: %d", p2);
        sscanf(text, "Draws : %d", dr);
    }

    fclose(fp);
}


void showScoreboard()
{
    FILE *fp = fopen("game_result.txt", "r");
    if(fp == NULL)
    {
        printf("\nNo scoreboard found!\n");
        return;
    }

    printf("\n=== SCOREBOARD ===\n");
    

    char line[200];
    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}
