
#include "Functions2Header.h"


// The function prints the board and returns how many nodes removed from the list.
int display(movesList* moves_list, boardPos start, char** board)
{
	
	int counter;
	counter = checksVaild(moves_list, start, board);
	printBoardQ2(board);
	return counter;
}

int checksVaild(movesList* moves_list, boardPos start, char** board)
{
	int counterToDelete = 0, Row, Col;
	char Rmove, Cmove, counterMoves = 0;

	moveCell* curr = moves_list->head;
	Row = start[0]-'A';
	Col = start[1];
	board[Row][Col] = '#'; // update the current spot to '#'


	//Condition to check all the nodes in "moves_list"
	while (curr != NULL)
	{
		// Update the current moves 
		Rmove = curr->move.rows;
		Cmove = curr->move.cols;
		//Condition to check invalid move
		if ((Col + Cmove < 0) || (Row + Rmove < 0) || (Row + Rmove >= N) || (Col + Cmove >= M) || board[Row + Rmove][Col + Cmove] != ' ' || board[Row + Rmove][Col + Cmove] == '*')
		{
			// Count invalid moves
			counterToDelete++;
			// Remove the current node and update the list 
			curr = removeFromListAndUpdateCurr(moves_list, &curr);
		}
		else
		{
			// Count valid moves
			counterMoves++;
			//Calculate the indexs and update the current spot to "counterMoves" result.
			board[Row + Rmove][Col + Cmove] = counterMoves;
			// Update row ,column and curr;
			Row = Row + Rmove;
			Col = Col + Cmove;
			curr = curr->next;
		}

	}

	return counterToDelete;

}

// The function prints the board
void printBoardQ2(char** board)
{
	int i, j, k = 0, counter = 0, row, col;
	for (i = 1; i <= (5 + ((N - 1) * 2)); i++)
	{
		for (j = 1; j <= (5 + ((M - 1) * 2)); j++)
		{
			if ((i % 2) == 1 && (j % 2) == 1)
				printf(" * ");
			if (i % 2 == 0 && j % 2 == 1)
				printf(" | ");
			if (i % 2 == 1 && j % 2 == 0)
				printf(" - ");
			if ((i % 2) == 0 && (j % 2) == 0 && i == 2)
			{
				if (counter == 0)
					counter++;
				else
				{
					printf(" %d ", counter-1);
					counter++;
				}
			}
			if ((i % 2) == 0 && (j % 2) == 0 && j == 2)
			{
				if (k == 0)
					k++;
				else
				{
					printf(" %c ", 'A' + (k - 1));
					k++;
				}
			}
			if (i == 2 && j == 2)
			{
				printf("   ");
			}
			if (i % 2 == 0 && j % 2 == 0 && i != 2 && j != 2)
			{
				col = (j - 4) / 2;
				row = (i - 4) / 2;
				if (board[row][col] == '*' || board[row][col] == ' ' || board[row][col] == '#')
					printf(" %c ", board[row][col]);
				else
				{
					if (board[row][col] <= 9)
						printf(" %d ", board[row][col]);
					else
						printf(" %d", board[row][col]);

				}
			}
		}
		printf("\n");
	}
}
