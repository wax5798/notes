/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月03日 星期六 15时38分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX(a, b) (a > b ? a : b)

int longestCommonSubsequence(char * text1, char * text2){
	int index1 = 0, index2 = 0;
	int len1 = strlen(text1), len2 = strlen(text2);
	int dp[1000][1000] = {0};

	for (index1 = 1; index1 < len1 + 1; index1 ++)
	{
		for (index2 = 1; index2 < len2 + 1; index2 ++)
		{
			if (text1[index1 - 1] == text2[index2 - 1])
			{
				dp[index1][index2] = dp[index1 - 1][index2 - 1] + 1;
			}
			else
			{
				dp[index1][index2] = MAX(dp[index1 - 1][index2], dp[index1][index2 - 1]);
			}
		}
	}

	return dp[len1][len2];
}

int main(int argc, char *argv[])
{
	int i = 0;
	char *strList[][2] = {{"abcde", "ace"}, {"abc", "abc"}, {"abc", "def"}};

	for (; i < sizeof(strList) / sizeof(strList[0]); i ++)
	{
		printf("text1: %s, text2: %s, maxLen: %d\n", strList[i][0], strList[i][1], longestCommonSubsequence(strList[i][0], strList[i][1]));
	}
	return 0;
}
