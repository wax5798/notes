/*************************************************************************
	> File Name: leetcode.c
	> Author: wan xiangjun
	> Mail: 
	> Created Time: 2017年04月14日 星期五 22时51分22秒
 ************************************************************************/

#include<stdio.h>
 
#define CODE_DEBUG 1
#if CODE_DEBUG
#define PRINTF printf
#else
#define PRINTF
#endif  

/*这道题貌似不用排序？题目中并没有说明给定的时间点是按顺序的吧？*/
void leetSort(int *nums, int numsSize) {
    int i, j;
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

int findPoisonedDuration(int* timeSeries, int timeSeriesSize, int duration) {
    int i, j;
    int total = 0;
    int start, end;

    leetSort(timeSeries, timeSeriesSize);
    
    for (i = 0; i < timeSeriesSize;) {
        start = timeSeries[i];
        end = timeSeries[i] + duration;
        i ++;
        while (i < timeSeriesSize) {
            if (timeSeries[i] <= end) {
                end = timeSeries[i] + duration;
                i ++;
            } else {
                break;
            }
        }
        total += end - start;
    }

    return total;
}
