/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年03月25日 星期四 22时23分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* #define DEBUG_ON */

static int length_of_last_word(const char *oriStr)
{
	int count = 0;
	int lastCount = 0;
	int len = strlen(oriStr);
	int i = 0;

	for (; i < len; i ++)
	{
		if ((oriStr[i] >= 'a') && (oriStr[i] <= 'z'))
		{
			count ++;
			continue;
		}

		if ((oriStr[i] >= 'A') && (oriStr[i] <= 'Z'))
		{
			count ++;
			continue;
		}

		lastCount = count;
		count = 0;
	}

	return count ? count : lastCount;
}

#ifdef DEBUG_ON
char *test[] = {
	"hello nowcoder", 
	"hello New Coder"
};

static void test_func() 
{
	int i = 0;
	int testNum = sizeof(test)/sizeof(test[0]);

	for (; i < testNum; i ++) {
		printf("[%d] ori string: %s, length of last word: %d\n", i, test[i], length_of_last_word(test[i]));
	}
}
#endif
 

#define MAX_INPUT_LEN 5000

int main(int argc, char *argv[]) 
{
#ifdef DEBUG_ON
	test_func();
#else
	char inputStr[MAX_INPUT_LEN + 1] = {0};

	fgets(inputStr, sizeof(inputStr), stdin);
	printf("%d\n", length_of_last_word(inputStr));
#endif

	return 0;
}
