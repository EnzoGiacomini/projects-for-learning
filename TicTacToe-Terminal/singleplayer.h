#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "common.h"

void single(Data *g);
void playSingle(Data *g, int *r, int ia);
void iaEasy(Data *g);
void iaNormal(Data *g);
int testPlace(Data *g, int m);
int testGame(int tempBoard[3][3], int turn);
void copyBoard(Data *g, int copyBoard[3][3]);
void decoderInputBOT(int m, Data *g);
void chooseDifficult(int *ia);
void iaHard(Data *g);
int evaluateMove(int board[3][3]);
int minMax(int board[3][3], int depth, int isMax);
int isMovesLeft(int board[3][3]);


#endif