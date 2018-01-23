/*************************************************************************
	> File Name: main.c
	> Author: wan xiangjun
	> Mail: 
	> Created Time: 2017年11月07日 星期二 22时19分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOLUTION_BRANCH 2

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 1 == SOLUTION_BRANCH
int* twoSum(int* nums, int numsSize, int target) {
    int i, j;
    int *reVal = malloc(2 * sizeof(int));
    int numToFind;
    
    printf("This is branch %d\n", SOLUTION_BRANCH);
    for (i = 0; i < numsSize; i ++) {
        numToFind = target - nums[i];
        for (j = i + 1; j < numsSize; j ++) {
            if (nums[j] == numToFind) {
                reVal[0] = i;
                reVal[1] = j;
                return reVal;
            }
        }
    }
    
    return reVal;
}
#endif

#if 2 == SOLUTION_BRANCH
int* twoSum(int* nums, int numsSize, int target) {
    int min = 0x7FFFFFFF;
    int max, len, i;
    int *hash;
    int *reVal = malloc(2 * sizeof(int));

    printf("This is branch %d\n", SOLUTION_BRANCH);
    for (i = 0; i < numsSize; i ++) {
        min = min > nums[i] ? nums[i]:min;
    }
    max = target - min;
    len = max - min + 1;

    hash = malloc(len * sizeof(int));
    for (i = 0; i < len; i ++) {
        hash[i] = -1;
    }

    for (i = 0; i < numsSize; i ++) {
        if (target - min < nums[i]) {
            continue;
        }

        if (hash[target - nums[i] - min] != -1) {
            reVal[0] = hash[target - nums[i] - min];
            reVal[1] = i;
            free(hash);
            return reVal;
        }

        hash[nums[i] - min] = i;
    }
    
    free(hash);
    return reVal;
}
#endif

int main(int argc, char *argv[])
{
    int nums[] = {2, 7, 11, 15};  
    int target = 9;
    int *res = twoSum(nums, sizeof(nums) / sizeof(nums[0]), target);
    printf("res is [%d, %d]\n", res[0], res[1]);
    free(res);
    return 0;
}
