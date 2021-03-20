#include "FunctionsHeader.h"



//The function  updates the version of mainMoves According to "board" and then 
//creates an Array that knows all the legal movement indexes from each spot
boardPosArray** validMoves(movesArray** mainMoves, char** board)
{
    validMovesHelper(mainMoves, board);
    //creates boardPosArray after updating mainMoves
    boardPosArray** result;
    result = (boardPosArray**)malloc(N * sizeof(boardPosArray*));
    createBoardPosArray(result, mainMoves);
    return result;
    
}

void changemainArray(movesArray** mainMove, int starRow, int starCol)
{
    int Rindex;
    int Cindex;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            Rindex = starRow - i;
            Cindex = starCol - j;
            if (starRow != i || starCol != j)
            {
                changeMinorArray(mainMove[i][j].moves, Rindex, Cindex, mainMove[i][j].size);
                mainMove[i][j].size = mainMove[i][j].size - 1;
            }
        }
    }
}

void changeMinorArray(Move* specificMove, int Rindex, int Cindex, int size)
{
    int sign = 0;
    for (int i = 0; i < size; i++)
    {
        if (((specificMove[i].cols) == Cindex) && ((specificMove[i].rows) == Rindex))
        {
            sign = 1;
        }
        if (sign == 1)
        {
            specificMove[i].cols = specificMove[i + 1].cols;
            specificMove[i].rows = specificMove[i + 1].rows;
        }
    }
   
}

void createBoardPosArray(boardPosArray**  result,movesArray** mainMoves) 
{
    for (int i = 0; i < N; i++)
    {
        result[i] = (boardPosArray*)malloc(M * sizeof(boardPosArray));
        for (int j = 0; j < M; j++)
        {
            result[i][j].positions= (boardPos*)malloc((mainMoves[i][j].size) * sizeof(boardPos));
            for (unsigned int index = 0; index < mainMoves[i][j].size; index++)
            {
                result[i][j].positions[index][0] = i+(mainMoves[i][j].moves[index].rows);
                result[i][j].positions[index][1] = j+(mainMoves[i][j].moves[index].cols);
                result[i][j].size = mainMoves[i][j].size;
            }
        }
    }
}


void validMovesHelper(movesArray** mainMoves, char** board)
{
    for (int starRow = 0; starRow < N; starRow++)
    {
        for (int starCol = 0; starCol < M; starCol++)
        {
            //Condition to know where the stars locaed at "board"
            //and which index to change in mainMoves cells
            if (board[starRow][starCol] == '*')
            {
                changemainArray(mainMoves, starRow, starCol);
            }
        }
    }
}


