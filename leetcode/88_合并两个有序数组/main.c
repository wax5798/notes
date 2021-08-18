/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月05日 星期一 10时49分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
	int im = m - 1, in = n - 1;

	while ((im >= 0) || (in >= 0))
	{
		while (in >= 0)
		{
			if ((im < 0) || (nums2[in] >= nums1[im]))
			{
				nums1[im + in + 1] = nums2[in];
				in --;
				continue;
			}

			break;
		}

		if (im >= 0)
		{
			nums1[im + in + 1] = nums1[im];
			im --;
		}
	}
}

int main(int argc, char *argv[])
{
	int i = 0;
	int nums1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; /* 检测数组的其他内容是否被非法修改 */
	int nums2[] = {1};
	int m = 0, n = 1;

	merge(nums1 + 3, m + n, m, nums2, n, n);

	for (i = 0; i < 9; i ++)
	{
		printf("%d ", nums1[i]);
	}
	printf("\n");

	return 0;
}

#if 0
	int nums1[] = {1,2,3,0,0,0};
	int nums2[] = {2, 5, 6};
	int m = 3, n = 3;
#endif
#if 0
	int nums1[] = {3,4,6,9,0, 0,0};
	int nums2[] = {2, 5, 6};
	int m = 4, n = 3;
#endif
