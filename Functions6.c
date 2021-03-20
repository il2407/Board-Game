#define _CRT_SECURE_NO_WARNINGS
#include "Functions6Header.h"


int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	//Updating moves array according to board
	validMovesHelper(moves, board);
	FILE* posFile;
	posFile=fopen(file_name, "rb");
	fileOpenCheck(posFile);
	short int size;
	fread(&size, sizeof(short int), 1, posFile);
	//Creating empty bit board to have a platform for reading data from binFile
	boardPos* arr = createEmptyBitBoard(size);
	//Building relevant masks for reading data
	unsigned char* masks = BuildMasksArr();
	//Uncompressing th file to an array
	arr = unCompressFunc(posFile, size, arr, masks);
	int preCheck = 0;
	//Checking if the route is empty or with one spot
	preCheck = checkEdgeCondition(arr, size, board);
	if (preCheck!= -1) return preCheck;

	boardPos start;
	start[0] = (arr[0][0]-'0');
	start[1] = (arr[0][1] - '0');
	movesList validList;
	makeEmptyList(&validList);
	int resultNum = 0;
	resultNum=checkRoute_MakeList(arr, &validList, size, moves, board);
	if (resultNum == 1) return resultNum;
	start[0] = start[0] + 'A';
	display(&validList, start, board);
	free(arr);
	free(masks);
	return resultNum;	
}

unsigned char* BuildMasksArr()
{

	int j;
	unsigned char* masks = (unsigned char*)malloc(sizeof(unsigned char) * 10);
	checkMemoryAllocation(masks);

	for (j = 0; j < 10; j++)
	{
		if (j == 0)
			masks[j] = 0xE0;
		if (j == 1)
			masks[j] = 0x1C;
		if (j == 2)
			masks[j] = 0x03;
		if (j == 3)
			masks[j] = 0x80;
		if (j == 4)
			masks[j] = 0x70;
		if (j == 5)
			masks[j] = 0x0E;
		if (j == 6)
			masks[j] = 0x01;
		if (j == 7)
			masks[j] = 0xC0;
		if (j == 8)
			masks[j] = 0x38;
		if (j == 9)
			masks[j] = 0x07;
	}
	return masks;
}

boardPos* createEmptyBitBoard(short int size)
{
	boardPos* arr;
	arr = (boardPos*)malloc(sizeof(boardPos) * size);
	checkMemoryAllocation(arr);
	for (int i = 0; i < size; i++)
	{
		arr[i][0] = '\0';
		arr[i][1] = '\0';

	}
	return arr;
}

boardPos*  unCompressFunc(FILE* posFile, short int size,boardPos* arr,unsigned char* masks)
{

	int maskIndex, bitCounter, i;
	bitCounter = 0;
	maskIndex = 0;
	i = 0;
	unsigned char curr;
	while (i < size)
	{
		fread(&curr, sizeof(unsigned char), 1, posFile);
		arr[i][0] = (((curr & (masks[bitCounter % 10])) >> 5) + '0');
		bitCounter++;
		arr[i][1] = (((curr & (masks[bitCounter % 10])) >> 2) + '0');
		bitCounter++;
		i++;
		if (i == size) break;
		arr[i][0] = (((curr & (masks[bitCounter % 10])) << 1) + '0');
		bitCounter++;
		////////////////BYTE Seperation/////////////////
		fread(&curr, sizeof(unsigned char), 1, posFile);
		arr[i][0] = ((arr[i][0]) | ((curr & (masks[bitCounter % 10])) >> 7) + '0');
		bitCounter++;
		arr[i][1] = (((curr & (masks[bitCounter % 10])) >> 4) + '0');
		bitCounter++;
		i++;
		if (i == size) break;
		arr[i][0] = (((curr & (masks[bitCounter % 10])) >> 1) + '0');
		bitCounter++;
		arr[i][1] = (((curr & (masks[bitCounter % 10])) << 2) + '0');
		bitCounter++;
		/////////////// BYTE Seperation/////////////////
		fread(&curr, sizeof(unsigned char), 1, posFile);
		arr[i][1] = ((arr[i][1]) | ((curr & (masks[bitCounter % 10])) >> 6) + '0');
		bitCounter++;
		i++;
		if (i == size) break;
		arr[i][0] = (((curr & (masks[bitCounter % 10])) >> 3) + '0');
		bitCounter++;
		arr[i][1] = (((curr & (masks[bitCounter % 10])) >> 0) + '0');
		bitCounter++;
		i++;

	}
	return arr;
}

int checkRoute_MakeList(boardPos* arr, movesList* validList,short int size,movesArray** moves, char** board)
{

	int checkRow, checkCol ,moveCheckRow, moveCheckCol;
	checkRow = checkCol = moveCheckRow = moveCheckCol = 0;
	int index, listSize, checkFlag;
	listSize = index = checkFlag = 0;
	int checkArr[N][M];
	//Create an array of '0' integers  to be a check array for repeating spots
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			checkArr[r][c] = 0;
		}
	}
	while (index < size - 1)
	{
		checkRow = arr[index][0] - '0';
		checkCol = arr[index][1] - '0';
		//Checks if we've been at this spot already and if true
		//the index continues and ignore
		while (checkArr[checkRow][checkCol] > 0)
		{
			checkArr[checkRow][checkCol]++;
			index++;
			checkRow = arr[index][0] - '0';
			checkCol = arr[index][1] - '0';
		}
		checkArr[checkRow][checkCol]++;
		index++;
	    //Cuclalate the movement between curr spot to next spot 
		moveCheckRow = (arr[index][0] - '0') - checkRow;
		moveCheckCol = (arr[index][1] - '0') - checkCol;
		//Checks if we've been at the next spot already and if true
		//the index continues and ignore
		while (checkArr[arr[index][0] - '0'][arr[index][1] - '0'] > 0)
		{
			checkArr[arr[index][0] - '0'][arr[index][1] - '0']++;
			index++;
			moveCheckRow = (arr[index][0] - '0') - checkRow;
			moveCheckCol = (arr[index][1] - '0') - checkCol;
		}
		//Condition : check if there is a star at curr spot or next spot 
		if (board[checkRow][checkCol] == '*' || board[arr[index][0] - '0'][arr[index][1] - '0'] == '*') return 1;
		for (int movesIndex = 0;(unsigned) movesIndex < moves[checkRow][checkCol].size; movesIndex++)
		{
			//Condition : check if the movement is legal from curr spot
			if (moveCheckRow == (moves[checkRow][checkCol].moves[movesIndex].rows) && moveCheckCol == (moves[checkRow][checkCol].moves[movesIndex].cols))
			{
				checkFlag++;
				listSize++;
				insertDataToEndList(validList, moveCheckRow, moveCheckCol);
			}
		}
		if (checkFlag == 0)
			return 1;
		checkFlag = 0;
	}
	checkRow = arr[index][0];
	checkCol = arr[index][1];
	//Condition : check if the last spot is free put it in the list 
	if (checkArr[checkRow][checkCol] == 0)
	{
		listSize++;
		insertDataToEndList(validList, checkRow, checkCol);
	}
	//Condition : check if the listSize(amount of movements in list)
	//is same as the free spots in board
	if (listSize == legalSpotCounter(board)) return 2;
	return 3;
}

int checkEdgeCondition(boardPos* arr,short int size,char** board)
{
	if (size == 0)return 2;
	else if (size == 1)
	{
		if ((board[arr[0][0]-'0'][arr[0][1]-'0']) == '*') return 1;
		else return 2;
	}
	else return -1;
}