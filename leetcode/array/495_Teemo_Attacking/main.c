/*************************************************************************
	> File Name: main.c
	> Author: wan xiangjun
	> Mail: 
	> Created Time: 2017年04月14日 星期五 23时10分21秒
 ************************************************************************/

#include<stdio.h>


int main(int argc, char **argv) 
{
    int nums[] = {1, 4, 3, 8};
    int duration = 3;

    printf("poison time: %d\n", findPoisonedDuration(nums, sizeof(nums) / sizeof(int), duration));

    return 0;
}
