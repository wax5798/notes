/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年05月07日 星期五 19时39分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int xorOperation(int n, int start){
	int i = 0;
	int ret = 0;


	for (i = 0; i < 32; i ++) {
		int cone = 0;

		if (0 == (start & (1 << i))) {
		} else {
		}
	}
}

int main(int argc, char *argv[])
{
	int i = 0;
	int list[][2] = {
		{5, 0},
		{4, 3},
		{1, 7},
		{10, 5}
	};

	for (; i < sizeof(list) / sizeof(list[0]); i ++)
	{
		printf("n = %d, start = %d， res: %d\n", 
				list[i][0], list[i][1], xorOperation(list[i][0], list[i][1]));
	}

	return 0;
}
