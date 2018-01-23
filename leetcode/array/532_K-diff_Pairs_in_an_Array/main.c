/*************************************************************************
	> File Name: main.c
	> Author: wan xiangjun
	> Mail: 
	> Created Time: 2017年04月13日 星期四 23时20分07秒
 ************************************************************************/

#include<stdio.h>

extern int findPairs(int* nums, int numsSize, int k);

int main(int argc, char **argv) {
    int k = 2;
    int nums[] = {-1, -2, -3};
    printf("while k = %d, k pairs is %d\n", k, 
            findPairs(nums, sizeof(nums)/sizeof(int), k));

    return 0;
}

