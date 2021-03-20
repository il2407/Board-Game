#define _CRT_SECURE_NO_WARNINGS
#include "Functions5Header.h"


void saveListToBinFile(char* file_name, boardPosArray* pos_arr)
{
	short int size, byteSize;
	FILE* binFile;
	size = pos_arr->size;
	byteSize = ((size * 6) / 8) + 1;
	unsigned char* arr = (unsigned char*)malloc(sizeof(unsigned char) * byteSize);
	checkMemoryAllocation(arr);
	for (int i = 0; i < byteSize; i++)
		arr[i] = '\0';

	binFile = fopen(file_name, "wb");
	fileOpenCheck(binFile);
	fwrite(&size, sizeof(short int), 1, binFile);
	arr = compressToArr(arr, size, pos_arr);
	for (int i = 0; i < byteSize; i++)
	      fwrite(&(arr[i]), sizeof(unsigned char), 1, binFile);

	free(arr);
	fclose(binFile);

}

unsigned char* compressToArr(unsigned char* arr,short int size,boardPosArray* pos_arr)
{
	int  i = 0, byteIndex = 0, bitCounter = 0;
	while (i < size)
	{
		byteIndex = bitCounter / 8;
		if (byteIndex % 3 == 0)
		{
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)pos_arr->positions[i][0]) - '0') << 5);
			bitCounter = bitCounter + 3;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 2);
			bitCounter = bitCounter + 3;
			i++;
			if (i == size) break;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][0])) - '0') >> 1);
			bitCounter = bitCounter + 3;
			byteIndex++;
		}

		if (byteIndex % 3 == 1)
		{
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][0])) - '0') << 7);
			bitCounter = bitCounter + 3;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 4);
			bitCounter = bitCounter + 3;
			i++;
			if (i == size) break;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 1);
			bitCounter = bitCounter + 3;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') >> 2);
			bitCounter = bitCounter + 3;
			byteIndex++;
		}
		if (byteIndex % 3 == 2)
		{
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 6);
			bitCounter = bitCounter + 3;
			i++;
			if (i == size) break;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 3);
			bitCounter = bitCounter + 3;
			arr[byteIndex] = arr[byteIndex] | ((((unsigned char)(pos_arr->positions[i][1])) - '0') << 0);
			bitCounter = bitCounter + 3;
			i++;
			if (i == size) break;
			byteIndex++;
		}

	}
	return arr;
}