#ifndef FUNCTIONS4HEADER_H
#define  FUNCTIONS4HEADER_H
#include "General.h"
#include "Functions3Header.h"


//Q4:
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int findPathCoveringAllBoardHelper(boardPos start, treeNodeListCell* currNode, int  size, int pathSize, moveCell* currCell, moveCell* tail);
int legalSpotCounter(char** board);

#endif