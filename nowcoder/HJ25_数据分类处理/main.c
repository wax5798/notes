/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年03月26日 星期五 21时02分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define uint_32 unsigned int

void insert_in_sort(uint_32 *array, uint_32 count, uint_32 newNum)
{
	int i = count - 1;

	for (; i >= 0; i --)
	{
		if (newNum >= array[i])
		{
			break;
		}
		array[i + 1] = array[i];
	}

	array[i + 1] = newNum;
}

uint_32 find_in_I(uint_32 *iArray, uint_32 iCount, uint_32 rData, uint_32 *oArray)
{
	int totalCount = 0;
	int i = 0;
	char rStr[32] = {0}, iStr[32] = {0};

	snprintf(rStr, sizeof(rStr), "%d", rData);
	for (; i < iCount; i ++)
	{
		/* 重复的操作，空间换时间？ */
		snprintf(iStr, sizeof(iStr), "%d", iArray[i]);
		if (strstr(iStr, rStr))
		{
			oArray[totalCount * 2] = i;
			oArray[totalCount * 2 + 1] = iArray[i];
			totalCount ++;
		}
	}

	return totalCount;
}

uint_32 res_calc(uint_32 *iArray, uint_32 iCount, uint_32 *rArray, uint_32 rCount, uint_32 outSize, int needPrint)
{
	int i = 0, j = 0;
	uint_32 outCount = 0, findCount = 0;
	uint_32 *oArray = NULL;

	if (needPrint) printf("%d ", outSize);

	oArray = malloc(sizeof(uint_32) * iCount * 2);
	for (; i < rCount; i ++)
	{
		if ((i > 0) && (rArray[i] == rArray[i - 1]))
		{
			continue;
		}

		if (0 == (findCount = find_in_I(iArray, iCount, rArray[i], oArray)))
		{
			continue;
		}

		outCount += 2 + findCount * 2;
		if (needPrint) 
		{
			printf("%d ", rArray[i]);
			printf("%d ", findCount);
		}

		for (j = 0; j < findCount * 2; j ++)
		{
			if (needPrint) printf("%d ", oArray[j]);
		}
	}
	if (needPrint) printf("\n");

	free(oArray);

	return outCount;
}

int main(int argc, char *argv[])
{
	uint_32 iCount = 0, rCount = 0;
	/* negative not considered ? */
	uint_32 *iArray = NULL, *rArray = NULL;
	uint_32 ii = 0, ir = 0;
	uint_32 tmp = 0;
	uint_32 outSize = 0;

	while (1)
	{
		if (EOF == scanf("%u", &iCount)) break;
		iArray = malloc(sizeof(uint_32) * iCount);
		for (ii = 0; ii < iCount; ii ++)
		{
			scanf("%u", iArray + ii);
		}

		scanf("%u", &rCount);
		rArray = malloc(sizeof(uint_32) * rCount);
		for (ir = 0; ir < rCount; ir ++)
		{
			scanf("%u", &tmp);
			insert_in_sort(rArray, ir, tmp);
		}

		/* 重复计算两次，利用时间换空间 */
		outSize = res_calc(iArray, iCount, rArray, rCount, outSize, 0);
		res_calc(iArray, iCount, rArray, rCount, outSize, 1);

		free(iArray);
		free(rArray);
	}

	return 0;
}
