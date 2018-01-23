/*************************************************************************
	> File Name: 532_K-diff_Pairs_in_an_Array.c
	> Author: wan xiangjun
	> Mail: 
	> Created Time: 2017年04月13日 星期四 21时57分45秒
 ************************************************************************/

#include<stdio.h>

#define CODE_DEBUG 1
#if CODE_DEBUG
#define PRINTF printf
#else
#define PRINTF
#endif  

void leetSort(int *nums, int numsSize) {
    int i = 0, j = 0;
    int tmp;

    for (i = 0; i < numsSize; i ++) {
        for (j = i + 1; j < numsSize; j ++) {
            if (nums[i] > nums[j]) {
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
    }
}

int leetCheckRepeat(int *nums, int *pNumsSize) {
    int numsSize = *pNumsSize;
    int i = 0, j = 0;
    int repeatNum = 0;
    int lastRepeat = 0;

    for (i = 1; i < numsSize; i ++) {
        if (nums[i] != nums[j]) {
            nums[++j] = nums[i];
            continue;
        }
        if (0 == repeatNum) {
            repeatNum ++;
            lastRepeat = nums[i];
            continue;
        }

        if (lastRepeat != nums[i]) {
            repeatNum ++;
            lastRepeat = nums[i];
        }
    }

    *pNumsSize = j + 1;
    return repeatNum;
}

int leetSearch(int *nums, int numsSize, int num) {
    int start = 0, end = numsSize - 1;
    int i = 0;

    while ((end - start) > 1) {
        i = (end + start) / 2;
        if (num == nums[i]) {
            return i;
        } else if (num > nums[i]) {
            start = i;
        } else {
            end = i;
        }
    }

    if (num == nums[start]) {
        return start;
    }
    if (num == nums[end]) {
        return end;
    }
    return -1;
}

int leetKPairs(int *nums, int numsSize, int k) {
    int i = 1, j = 0;
    int kPairs = 0;
    int index = 0;

    for (i = 0; i < numsSize; i ++) {
        PRINTF("%d ", nums[i]);
    }

    for (i = 0; i < numsSize; i ++) {
        if ((index = leetSearch(nums, numsSize, k + nums[i])) < 0) {
            continue;
        }
        PRINTF("\npair (%d, %d)\n", nums[i], nums[index]);
        kPairs ++;
    }
    
    return kPairs;
}

int findPairs(int* nums, int numsSize, int k) {
    int repeatNum = 0;

    if ((0 == numsSize) || (k < 0)) {
        return 0;
    }

    leetSort(nums, numsSize);
    repeatNum = leetCheckRepeat(nums, &numsSize);
    PRINTF("repeat nums %d\n", repeatNum);

    if (0 == k) {
        return repeatNum;
    }

    return leetKPairs(nums, numsSize, k);
}


