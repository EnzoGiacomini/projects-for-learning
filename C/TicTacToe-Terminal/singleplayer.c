#include "singleplayer.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Top function for singleplayer mode
void single(Data *g)
{
    int gameResult = -1;
    int iaLevel;

    g->numPlays = 0;

    g->gameMode = 1;

    lineUi();
    printf("\tSINGLEPLAYER");
    lineUi();

    getUserNames(g, 0);

    sortPlayer(g);

    chooseDifficult(&iaLevel);

    do
    {
        playSingle(g, &gameResult, iaLevel);
    } while(g->gameMode != 0);

    endGame(gameResult, g);
}

void playSingle(Data *g, int *r, int ia)
{
    int move;

    printf("PLAYER: %s TURN!\n\n", g->nameTurn);

    if(g->turn == 0)
    {
        showBoard(0, g);

        printf("Move position (1-9): ");

        move = getOp();
    
        decoderInputPlayer(move, g);
    }
    else
    {
        switch (ia)
        {
        case 1:
            iaEasy(g);
            break;
        case 2:
            iaNormal(g);
            break;
        case 3: 
            iaHard(g);
            break;
        default:
            printf("\nSOMETHING WENT WRONG, PLEASE CHECK playSingle()!\n");
            break;
        }

        showBoard(0, g);
    }

    lineUi();

    checkGame(g, r);

    if(*r != 1 && *r != 0)
    {
        switchTurn(g);
    }

    g->numPlays++;
}

//IA MODES:
void iaEasy(Data *g)
{ //Just randomly choose a number
    int randomPlace = (rand() % 9) + 1;

    int i = (randomPlace - 1) / 3;
    int j = (randomPlace - 1) % 3;

    while(canPlace(i, j, g) != 1)
    {
        randomPlace = (rand() % 9) + 1;

        i = (randomPlace - 1) / 3;
        j = (randomPlace - 1) % 3;
    }

    g->board[i][j] = g->turn;
}

void iaNormal(Data *g)
{ //Try to win, block player, play at middle or play at corners. Else play anywhere
    int move = 1;

    while(testPlace(g, move) == 0 && move <= 9)
    {
        move++;
    }

    if(move == 10)
    {
        if(canPlace(1, 1, g) == 1)
        {
            g->board[1][1] = g->turn;
        }
        else if(canPlace(0,0,g) == 1)
        {
            g->board[0][0] = g->turn;
        }
        else if(canPlace(0,2,g) == 1)
        {
            g->board[0][2] = g->turn;
        }
        else if(canPlace(2,0,g) == 1)
        {
            g->board[2][0] = g->turn;
        }
        else if(canPlace(2,2,g) == 1)
        {
            g->board[2][2] = g->turn;
        }
        else if(g->numPlays != 9)
        {
            iaEasy(g);
        }
    }
    else
    {
        //Play where bot can win or player can win
        decoderInputBOT(move, g);
    }
    
}

void iaHard(Data *g)
{ // Try every option, using the best one... so it makes impossible to lose.
    int bestMove = -1;
    int board[3][3];
    int currentVal = -1000;
    int bestVal = -1000;

    copyBoard(g, board);

    for(int y = 1; y < 10; y++)
    {
        int i = (y - 1) / 3;
        int j = (y - 1) % 3;

        if(canPlace(i, j, g) == 1)
        {
            board[i][j] = 1;

            currentVal = minMax(board, 0, 0);

            if(currentVal > bestVal)
            {
                bestMove = y;
                bestVal = currentVal;
            }

            board[i][j] = -1;
        }
    }

    //Usa o melhor
    decoderInputBOT(bestMove, g);
}

//Hard ia functions
int minMax(int board[3][3], int depth, int isMax)
{   
    int score = evaluateMove(board);

    if(score == 10)
    {
        return score - depth;
    }

    if(score == -10)
    {
        return score + depth;
    }

    if(isMovesLeft(board) == 0)
    {
        return 0;
    }

    if(isMax == 1)
    {
        int best = -1000;

        for(int y = 1; y < 10; y++)
        {
            int i = (y - 1) / 3;
            int j = (y - 1) % 3;

            if(board[i][j] == -1)
            {
                board[i][j] = 1; 
                
                int val = minMax(board, depth + 1, 0); 

                if(val > best) {
                    best = val;
                }

                board[i][j] = -1;
            }
        }
        return best;
    }
    else 
    {
        int best = 1000;
        for(int y = 1; y < 10; y++)
        {
            int i = (y - 1) / 3;
            int j = (y - 1) % 3;

            if(board[i][j] == -1)
            {
                board[i][j] = 0; 
               
                int val = minMax(board, depth + 1, 1);
                
                if(val < best) {
                    best = val;
                }

                board[i][j] = -1; 
            }
        }
        return best;
    }
}

int evaluateMove(int board[3][3])
{
    //Testa linha
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != -1)
        {
            if(board[i][0] == 1)
            {
                return 10;
            }
            else
            {
                return -10;
            }
        }
    }
    //Testa coluna
    for(int j = 0; j < 3; j++)
    {
        if(board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != -1)
        {
            if(board[0][j] == 1)
            {
                return 10;
            }
            else
            {
                return -10;
            }
        }
    }
    //Teste diagonal principal
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != -1)
    {
        if(board[0][0] == 1)
        {
            return 10;
        }
        else
        {
            return -10;
        }
    }
    //Teste diagonal secundária
    else if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != -1)
    {
        if(board[0][2] == 1)
        {
            return 10;
        }
        else
        {
            return -10;
        }
    }
    //Teste empate
    else
    {
        return 0;
    }
}

int isMovesLeft(int board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == -1)
            {
                return 1;
            }
        }
    }
    return 0;
}
//End hard ia

//Others functions:
int testPlace(Data *g, int m)
{   
    int i = (m - 1) / 3;
    int j = (m - 1) % 3;


    //Test if BOT can win
    if(canPlace(i, j, g) == 0)
    {
        return 0;
    }

    int testResult, tempBoard[3][3];
    copyBoard(g, tempBoard);

    tempBoard[i][j] = g->turn;
    testResult = testGame(tempBoard, g->turn);

    if(testResult != 0) 
    {
        return testResult;
    }

    copyBoard(g, tempBoard);
    tempBoard[i][j] = !(g->turn);
    testResult = testGame(tempBoard, !(g->turn));

    return  testResult;
    
}

int testGame(int tempBoard[3][3], int turn)
{
    //Testa linha
    for(int i = 0; i < 3; i++)
    {
        if(tempBoard[i][0] == tempBoard[i][1] && tempBoard[i][1] == tempBoard[i][2] && tempBoard[i][0] != -1)
        {   
            if(turn == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    //Testa coluna
    for(int j = 0; j < 3; j++)
    {
        if(tempBoard[0][j] == tempBoard[1][j] && tempBoard[1][j] == tempBoard[2][j] && tempBoard[0][j] != -1)
        {
            if(turn == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    //Teste diagonal principal
    if(tempBoard[0][0] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][2] && tempBoard[0][0] != -1)
    {
        if(turn == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    //Teste diagonal secundária
    if(tempBoard[0][2] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][0] && tempBoard[0][2] != -1)
    {
        if(turn == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    
    return 0;
}

void decoderInputBOT(int m, Data *g)
{
    int i = (m - 1) / 3;
    int j = (m - 1) % 3;

    g->board[i][j] = g->turn;
}

void copyBoard(Data *g, int copyBoard[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            copyBoard[i][j] = g->board[i][j];
        }
    }
}

void chooseDifficult(int *ia)
{
    lineUi();
    printf("Please select the IA difficult: \n1 - Easy\n2 - Normal\n3 - Hard\n\n-> ");

    do
    {
        *ia = getOp();

        if(*ia > 3 || *ia < 0)
        {
            printf("ERROR, PLEASE ENTER A NUMBER BETWEEN 1 AND 3\n\n-> ");
        }
    } while(*ia > 3 || *ia < 0);

    lineUi();
}