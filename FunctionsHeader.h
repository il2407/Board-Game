#ifndef FUNCTIONSHEADER_H
#define  FUNCTIONSHEADER_H
#include "General.h"

//Q1:
boardPosArray** validMoves(movesArray** mainMoves, char** board);
void changemainArray(movesArray** mainMove, int starRow, int starCol);
void changeMinorArray(Move* specificMove, int Rindex, int Cindex, int size);
void createBoardPosArray(boardPosArray** result, movesArray** mainMoves);
void validMovesHelper(movesArray** mainMoves, char** board);

#endif