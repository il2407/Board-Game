#include "Functions3Header.h"



pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board)
{
    //Updating moves array according to board
    validMovesHelper(moves, board);
    //creating a tree:
    pathTree pt;
    treeNode* node;
    treeNodeListCell* head;
    //creating a tree head:
    node = (treeNode*)malloc(sizeof(treeNode));
    head = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkMemoryAllocation(node);
    checkMemoryAllocation(head);
    head->node = node;
    head->node->position[0] = start[0];
    head->node->position[1] = start[1];
    head->next = NULL;
    findAllPossiblePathsHelper(head, moves, board);
    pt.head = head->node;
    return pt;
}

void findAllPossiblePathsHelper(treeNodeListCell* currNode, movesArray** moves, char** board)
{
    boardPos start;
    //Creating board pos argument to tell "createList " function what to do
    start[0] = currNode->node->position[0];
    start[1] = currNode->node->position[1];
    int row = (int)start[0]-'A';
    int col = (int)start[1];
    //Updating the current spot as illegal from now on
    board[row][col] = '*';
    //Creating the list of the possible moves from this spot
    currNode->node->next_possible_positions = createList(start, moves, board);
    //recurtion condition : if the moves list isnt empty continue with the next treenode
    if (currNode->node->next_possible_positions != NULL)
    {
        findAllPossiblePathsHelper(currNode->node->next_possible_positions, moves, board);
    }
    //recurtion condition:makes list for every cell of the list

    if (currNode->next != NULL)
    {
        //updates the board to know that the prvious cell of the list is now llegal
        board[currNode->node->position[0]-'A'][currNode->node->position[1]] = ' ';
        findAllPossiblePathsHelper(currNode->next, moves, board);
    }
    //updates the board to know that the prvious cell of the list is now llegal

    board[currNode->node->position[0]-'A'][currNode->node->position[1]] = ' ';
}

treeNodeListCell* createList(boardPos start, movesArray** move, char** board)
{
    int currRow, currCol, moveRow, moveCol;
    currRow = (int)start[0]-'A';
    currCol = (int)start[1];
    moveRow = moveCol = 0;
    treeNodeListCell* curr, * head;
    head = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    curr = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkMemoryAllocation(head);
    checkMemoryAllocation(curr);
    unsigned int i = 0;
    int counter;
    counter = 0;
    //condition to check all the values in "move" array
    while (i < move[currRow][currCol].size)
    {
        //calculate the index that we want to add to the tree According to
        //legal steps data we have in "move" array
        moveRow = currRow + move[currRow][currCol].moves[i].rows;
        moveCol = currCol + move[currRow][currCol].moves[i].cols;
        //condition to check if the spot is legal
        if (board[moveRow][moveCol] != '*')
        {
            //Condition to check if that's the first spot of the list
            if (counter == 0)
            {
                head->node = (treeNode*)malloc(sizeof(treeNode));
                checkMemoryAllocation(head->node);
                head->node->position[0] = moveRow+'A';
                head->node->position[1] = moveCol;
                head->next = NULL;
                counter++;
            }
            else
            {
                //Condition to check if that's the second spot of the list
                //so we can connect between head and curr
                if (counter == 1)
                {
                    curr->node = (treeNode*)malloc(sizeof(treeNode));
                    checkMemoryAllocation(curr->node);

                    head->next = curr;
                }

                else
                {
                    curr->next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
                    curr->next->node = (treeNode*)malloc(sizeof(treeNode));
                    checkMemoryAllocation(curr->next);
                    checkMemoryAllocation(curr->next->node);
                    curr = curr->next;
                }
                curr->node->position[0] = moveRow+'A';
                curr->node->position[1] = moveCol;
                curr->next = NULL;
                counter++;
            }
        }
        //Moving on "move" array indexes
        i++;
    }
    if (counter == 0)
    {
        return NULL;
    }
    else
    {
        if (counter == 1)head->next = NULL;
        return head;
    }
}

void freeTree(treeNodeListCell* currNode)
{
    
    if (currNode->node->next_possible_positions != NULL)
    {
        freeTree(currNode->node->next_possible_positions);
    }
    if (currNode->next != NULL)
    {
        currNode = currNode->next;
        freeTree(currNode);
    }
    else     free(currNode);  
    
}