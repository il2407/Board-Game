#include "Functions4Header.h"

movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board)
{
    //Updating moves array according to board
    validMovesHelper(moves, board);
    pathTree pt;
    int size, flag; 
    flag = 0;
    movesList* path;
    path= (movesList*)malloc(sizeof(movesList));
    path->head= (moveCell*)malloc(sizeof(moveCell));
    path->tail= (moveCell*)malloc(sizeof(moveCell));
    //Calculating what is the length of the route should be to cover all board
    size = legalSpotCounter(board);
    //Creating a tree to know what all the possible paths are 
    pt = findAllPossiblePaths(start, moves, board);
    flag = (findPathCoveringAllBoardHelper(pt.head->position,pt.head->next_possible_positions, size - 1, 0,path->head,path->tail));
    freeTree(pt.head->next_possible_positions);
    free(pt.head);
    //Condition : flag >0 so we found a path that covers all board
    if (flag > 0)return (path);
    else return NULL;
}

int findPathCoveringAllBoardHelper(boardPos start, treeNodeListCell* currNode, int  size, int pathSize, moveCell* currCell,moveCell* tail)
{
    moveCell* nextCurr;
    if (pathSize == size)
    {
        currCell=(moveCell*)malloc(sizeof(moveCell));
        currCell = NULL;
        tail = currCell;
        return 1;
    }

    else
    {
        //recurtion condition : if the moves list isnt empty continue with the next treenode
        if (currNode->node->next_possible_positions != NULL)
        {
            currCell = insertDataToNode(start, currNode->node->position, currCell);
            nextCurr = currCell->next;
            nextCurr->prev = currCell;
            currCell = nextCurr;
            start[0] = currNode->node->position[0];
            start[1] = currNode->node->position[1];
            pathSize++;
            return 0 + findPathCoveringAllBoardHelper(start,currNode->node->next_possible_positions, size, pathSize, currCell,tail);
        }
        //recurtion condition:makes list for every cell of the list
        else
        {
            currCell = insertDataToNode(start, currNode->node->position, currCell);
            nextCurr = currCell->next;
            nextCurr->prev = currCell;
            currCell = nextCurr;
            start[0] = currNode->node->position[0];
            start[1] = currNode->node->position[1];
            pathSize++;
            if (pathSize == size)
            {
                currCell = (moveCell*)malloc(sizeof(moveCell));
                checkMemoryAllocation(currCell);
                currCell = NULL;
                return 1;
            }

        }
        if (currNode->next != NULL)
        {
            start[0] = currNode->next->node->position[0];
            start[1] = currNode->next->node->position[1];
            //Updates the board to know that the previous cell of the list is now legal
            return 0 + findPathCoveringAllBoardHelper(start,currNode->node->next_possible_positions, size, pathSize, currCell,tail);  
        }
        else
        {
            pathSize--;
        }
        //Updates the board to know that the prvious cell of the list is now llegal
        return 0;
    }
}

//Function Describe: counts how many free spots there are on the board
int legalSpotCounter(char** board)
{
    int counter;
    counter = 0;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (board[row][col] == ' ')counter++;
        }
    }
    return counter;
}
