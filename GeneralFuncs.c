#include "General.h"

/////////////List Funcs/////////////

moveCell* removeFromListAndUpdateCurr(movesList* moves_list, moveCell** curr)
{
	moveCell* ToRemoveFromList; // save it to remove the current node;
	ToRemoveFromList = *curr;
	*curr = (*curr)->next;
	removeNodeFromList(moves_list, ToRemoveFromList);
	return *curr;
}

void removeNodeFromList(movesList* moves_list, moveCell* res)
{
	moveCell* prev, * next;

	if (moves_list->head == res)
	{
		moves_list->head = res->next;
	}
	else if (moves_list->tail == res) {

		moves_list->tail = res->prev;
		moves_list->tail->next = NULL;
	}
	else {
		prev = res->prev;
		prev->next = res->next;
		next = res->next;
		next->prev = prev;

	}
	free(res);
}

void makeEmptyList(movesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

void insertDataToEndList(movesList* lst, char row, char col)
{
	moveCell* newTail;
	newTail = createNewListNode(row, col, lst->tail, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertNodeToEndList(movesList* lst, moveCell* tail)
{
	if (isEmptyList(lst) == true) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

bool isEmptyList(movesList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

moveCell* createNewListNode(char row, char col, moveCell* prev, moveCell* next)  //
{
	moveCell* res;
	res = (moveCell*)malloc(sizeof(moveCell));
	checkMemoryAllocation(res);
	res->move.rows = row;
	res->move.cols = col;
	res->next = next;
	res->prev = prev;
	return res;
}

moveCell* insertDataToNode(boardPos arr, boardPos nextArr, moveCell* curr)
{
	curr->move.rows = nextArr[0] - arr[0];
	curr->move.cols = nextArr[1] - arr[1];
	curr->next = (moveCell*)malloc(sizeof(moveCell));
	return curr;
}

/////////////Check Funcs/////////////

void  fileOpenCheck(FILE* fp)
{
	if (fp == NULL)
	{
		printf("error! ");
		exit(1);
	}
}

void checkMemoryAllocation(void* res)
{
	if (res == NULL)
	{
		printf("error! ");
		exit(1);
	}
}