#ifndef FUNCTIONS3HEADER_H
#define  FUNCTIONS3HEADER_H
#include "General.h"
#include "FunctionsHeader.h"

//Q3:
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);
void findAllPossiblePathsHelper(treeNodeListCell* currNode, movesArray** moves, char** board);
treeNodeListCell* createList(boardPos start, movesArray** moves, char** board);
void freeTree(treeNodeListCell* currNode);

#endif