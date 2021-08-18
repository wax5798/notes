/*************************************************************************
	> File Name: test1.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年03月27日 星期六 14时40分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


enum {
	TYPE_HDK,
	TYPE_CNY,
	TYPE_USD,
	TYPE_GBP
};

char *nameList[] = {"HKD", "CNY", "USD", "GBP"};
char chList[] = {"1234567890HKDCNYUSDGBPMAXMIN \n"};

int lineParse(const char *str, int *valueList, int *num, int *type, int *changMax)
{
	int i = 0;
	int len = strlen(str);
	char typeStr[32] = {0}, maxStr[32] = {0};

	for (i = 0; i < len; i ++)
	{
		if (NULL == strchr(chList, str[i]))
		{
			return -1;
		}
	}

	if (6 != sscanf(str, "%d %d %d %d %s %s", valueList + TYPE_CNY, valueList + TYPE_USD, 
				valueList + TYPE_GBP, num, typeStr, maxStr))
	{
		return -1;
	}

	for (i = TYPE_HDK; i <= TYPE_GBP; i ++)
	{
		if (!strcmp(nameList[i], typeStr))
		{
			*type = i;
			break;
		}
	}

	if (i > TYPE_GBP)
	{
		return -1;
	}

	if (!strcmp(maxStr, "MAX"))
	{
		*changMax = 1;
	}
	else if (!strcmp(maxStr, "MIN"))
	{
		*changMax = 0;
	}
	else
	{
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int valueList[4] = {0};
	int type = TYPE_HDK, num = 0;
	int changMax = 0;
	char tmpStr[512] = {0};

	while (NULL != fgets(tmpStr, sizeof(tmpStr), stdin))
	{
		if (lineParse(tmpStr, valueList, &num, &type, &changMax) < 0)
		{
			printf("ERROR\n");
			continue;
		}

		valueList[TYPE_GBP] = valueList[TYPE_GBP] * valueList[TYPE_USD] * valueList[TYPE_CNY];
		valueList[TYPE_USD] = valueList[TYPE_USD] * valueList[TYPE_CNY];
		valueList[TYPE_CNY] = valueList[TYPE_CNY];
		valueList[TYPE_HDK] = 1;

		num = num * valueList[type];
		if (changMax)
		{
			int i = TYPE_GBP;
			int firstValue = 1;

			for (; i >= TYPE_HDK; i --)
			{
				int count = 0;

				count = num / valueList[i];

				if (count) 
				{
					if (!firstValue) printf(" ");
					firstValue = 0;
					printf("%d %s", count, nameList[i]);
				}

				num = num % valueList[i];
			}
			printf("\n");
		}
		else
		{
			printf("%d HKD\n", num);
		}
	}

	return 0;
}
