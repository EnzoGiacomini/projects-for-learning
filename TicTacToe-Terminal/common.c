#include "common.h"
#include "multiplayer.h"
#include "singleplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Main Control Function:
void switchMode(int *op, Data *g)
{
    switch (*op)
    {
    case 1:
        cleanBoard(g);
        multi(g);
        break;
    case 2:
        cleanBoard(g);
        single(g);
        break;
    case 3:
        tutorial(g);
        break;
    case 4:
        //Do nothing
        break;
    default:
        printf("\nError, invalid option!\nPlease try again... \n-> ");
        *op = getOp();
        switchMode(op, g);
        break;
    }
}

//Others functions:
void cleanBoard(Data *g)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            g->board[i][j] = -1;
        }
    }
}

int getOp()
{
    char buffer[10];
    int op;

    fgets(buffer, 5, stdin);
    op = strtol(buffer, NULL, 10);

    return op;
}

void showBoard(int isTutorial, Data *g)
{
    if(isTutorial == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(j != 2)
                {
                    printf("  %c  |", intToChar(i, j, g));
                }
                else
                {
                    printf("  %c  ", intToChar(i, j, g));
                }
            }
            if(i != 2)
            {
                printf("\n-----+-----+-----\n");
            }
            else
            {
                printf("\n\n");
            }
        }
    }
    else
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(j != 2)
                {
                    printf("  %d  |", (i * 3) + j + 1);
                }
                else
                {
                    printf("  %d  ", (i * 3) + j + 1);
                }
            }
            if(i != 2)
            {
                printf("\n-----+-----+-----\n");
            }
            else
            {
                printf("\n\n");
            }
            
        }
    }
}

char intToChar(int i, int j, Data *g)
{
    if(g->board[i][j] == -1)
    {
        return ' ';
    }
    else if(g->board[i][j] == 0)
    {
        return 'X';
    }
    else
    {
        return 'O';
    }
}

void getUserNames(Data *g, int isMultiplayer)
{   

    if(isMultiplayer == 1)
    {
        printf("Please enter player 1 nickname: ");
        fgets(g->p1Name, 30, stdin);
        printf("Now, enter player 2 nickname: ");
        fgets(g->p2Name, 30, stdin);

        g->p1Name[strcspn(g->p1Name, "\n")] = '\0';
        g->p2Name[strcspn(g->p2Name, "\n")] = '\0';
    }
    else
    {
        printf("Please enter your nickname: ");
        fgets(g->p1Name, 30, stdin);

        strcpy(g->p2Name, "Bot");

        g->p1Name[strcspn(g->p1Name, "\n")] = '\0';
    }
    
    printf("\nDone!");
    lineUi();
}

void sortPlayer(Data *g)
{
    int randomNumber = rand() % 2;

    if(randomNumber == 0)
    {
        g->turn = 0;
        strcpy(g->nameTurn, g->p1Name);
    }
    else
    {
        g->turn = 1;
        strcpy(g->nameTurn, g->p2Name);
    }
}

int canPlace(int i, int j, Data *g)
{
    if(g->board[i][j] != -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void decoderInputPlayer(int m, Data *g)
{
    
    if (m < 1 || m > 9) {
        int new_m;

        printf("\n\nERROR, INVALID INPUT!\nTRY AGAIN\n\n");

        new_m = getOp();
        
        decoderInputPlayer(new_m, g);

        return; 
    }

    int i = (m - 1) / 3;
    int j = (m - 1) % 3;

    if(canPlace(i, j, g) == 1)
    {
        g->board[i][j] = g->turn;
    }
    else
    {
        int new_m;

        printf("\n\nERROR, NUMBER ALREADY CHOOSED!\nTRY AGAIN\n\n");

        new_m = getOp();

        decoderInputPlayer(new_m, g);
    }
    
}

void checkGame(Data *g, int *r)
{
    //Testa linha
    for(int i = 0; i < 3; i++)
    {
        if(g->board[i][0] == g->board[i][1] && g->board[i][1] == g->board[i][2] && g->board[i][0] != -1)
        {
            g->gameMode = 0;
            
            *r = 1;
        }
    }
    //Testa coluna
    for(int j = 0; j < 3; j++)
    {
        if(g->board[0][j] == g->board[1][j] && g->board[1][j] == g->board[2][j] && g->board[0][j] != -1)
        {
            g->gameMode = 0;
            
            *r = 1;
        }
    }
    //Teste diagonal principal
    if(g->board[0][0] == g->board[1][1] && g->board[1][1] == g->board[2][2] && g->board[0][0] != -1)
    {
        g->gameMode = 0;

        *r = 1;
    }
    //Teste diagonal secundária
    if(g->board[0][2] == g->board[1][1] && g->board[1][1] == g->board[2][0] && g->board[0][2] != -1)
    {
        g->gameMode = 0;

        *r = 1;
    }
    //Teste empate
    if(g->numPlays == 8 && *r != 1)
    {
        g->gameMode = 0;

        *r = 0;
    }
}

void switchTurn(Data *g)
{
    g->turn = !(g->turn);

    if(g->turn == 0)
    {
        strcpy(g->nameTurn, g->p1Name);
    }
    else
    {
        strcpy(g->nameTurn, g->p2Name);
    }
}

void endGame(int result, Data *g)
{
    if(result == 1)
    {
        printf("END GAME, WE HAVE A WINNER!\nCONGRATULATIONS %s", g->nameTurn);
        lineUi();
    }
    else
    {
        printf("OH WE HAVE A DRAWN!\nUNFORTNALY NOBODY WON...");
        lineUi();
    }
}
//End others functions.

//UI and Tutorial functions:
void lineUi()
{
    printf("\n\n-----------------------------------\n\n");
}

void startUi()
{
    lineUi();
    printf("\tTicTacToe Game!");
    lineUi();

    printf("Options:\n\n");
    printf("(Local Multiplayer - 1)\n");
    printf("(Singleplayer - 2)\n");
    printf("(How to play? - 3)\n");
    printf("(Exit - 4)");

    printf("\n\n-> ");
}

void tutorial(Data *g)
{   
    char c;

    lineUi();
    printf("\tHow to play:");
    lineUi();

    showBoard(1, g);

    lineUi();
    printf("When started your turn, you must input a number from 1-9, like the table show above.\nMake sure that your input isn't already marked!\n\n");
    printf("Press ENTER to get back to menu...");
    while((c = getchar()) != '\n');

}