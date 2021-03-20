#ifndef GENERAL_H
#define GENERAL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 4
#define M 4

//Structs:

typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move* moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos* positions;
} boardPosArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;

typedef struct _ListCell {
	Move moveData;
	struct _ListCell* next;
} ListCell;

typedef struct _List {
	ListCell* head;
	ListCell* tail;
} List;


typedef struct _treeNode {
	boardPos position;
	struct _treeNodeListCell* next_possible_positions; // מיקומים רשימת
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;


typedef struct _pathTree {
	treeNode* head;
} pathTree;


///////////Decleraions///////////////

//Memory Functions
void  fileOpenCheck(FILE* fp);
void checkMemoryAllocation(void* res);

//List Functions             
void makeEmptyList(movesList* lst);
void insertDataToEndList(movesList* lst, char row, char col);
void insertNodeToEndList(movesList* lst, moveCell* tail);
bool isEmptyList(movesList* lst);
moveCell* createNewListNode(char row, char col, moveCell* prev, moveCell* next);
void removeNodeFromList(movesList* moves_list, moveCell* res);
moveCell* removeFromListAndUpdateCurr(movesList* moves_list, moveCell** curr);
moveCell* insertDataToNode(boardPos arr, boardPos nextArr, moveCell* curr);


#endif