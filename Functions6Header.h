#ifndef FUNCTIONS6HEADER_H
#define  FUNCTIONS6HEADER_H
#include "General.h"
#include "Functions2Header.h"
#include "Functions4Header.h"

//Q6:
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
unsigned char* BuildMasksArr();
boardPos* createEmptyBitBoard(short int size);
boardPos* unCompressFunc(FILE* posFile, short int size, boardPos* arr, unsigned char* masks);
int checkRoute_MakeList(boardPos* arr, movesList* validList, short int size, movesArray** moves, char** board);
int checkEdgeCondition(boardPos* arr, short int size, char** board);

#endif
