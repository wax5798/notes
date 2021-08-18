/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月03日 星期六 16时32分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int bufFill(int base, int deep, int maxNum, int *buf, int index)
{
	int i = 0;

	for (i = 0; i < 10; i ++)
	{
		int curNum = base * 10 + i;
		if (0 == curNum) continue;

		if (curNum > maxNum) break;

		buf[index ++] = curNum;

		index = bufFill(curNum, deep + 1, maxNum, buf, index);
	}

	return index;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicalOrder(int n, int* returnSize){
	int *buf = NULL;

	buf = malloc(sizeof(int) * n);

	bufFill(0, 0, n, buf, 0);
	*returnSize = n;

	return buf;
}

int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int test_array[] = {13, 30, 8, 2000};

	for (i = 0; i < sizeof(test_array) / sizeof(test_array[0]); i ++)
	{
		int *array = NULL;
		int arrSize = 0;

		array = lexicalOrder(test_array[i], &arrSize);
		printf("n: %d, array: %d\n", test_array[i], arrSize);

		for (j = 0; j < arrSize; j ++)
		{
			printf("%d ", array[j]);
		}
		printf("\n");
	}

	return 0;
}
