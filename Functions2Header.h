#ifndef FUNCTIONS2HEADER_H
#define  FUNCTIONS2HEADER_H
#include "General.h"

// Q2:
// The function prints the board and returns how many nodes removed from the list.
int display(movesList* moves_list, boardPos start, char** board);
int checksVaild(movesList* moves_list, boardPos start, char** board);
void printBoardQ2(char** board);

#endif