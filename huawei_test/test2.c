/*************************************************************************
	> File Name: test2.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年03月27日 星期六 15时39分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int cpu_run(int *cpu, int m)
{
	int i = 0;
	int time = cpu[0];

	for(i = 0; i < m; i ++)
	{
		cpu[i] -= time;
	}

	return time;
}


int main(int argc, char *argv[])
{
	int i = 0, j = 0;
	int m = 0, n = 0;
	int t[1000] = {0};
	int cpu[1000] = {0};
	int totalTime = 0;

	scanf("%d %d", &m, &n);

	for (i = 0; i < n; i ++)
	{
		scanf("%d", &t[i]);
	}

	for (i = 0; i < n - 1; i ++)
	{
		for (j = i + 1; j < n; j ++)
		{
			int tmp = 0;
			if (t[i] > t[j])
			{
				tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			}
		}
	}

	if (m >= n)
	{
		printf("%d\n", t[n - 1]);
		return 0;
	}

	memcpy(cpu, t, sizeof(int) * m);

	totalTime += cpu_run(cpu, m);

	for (i = m; i < n; i ++)
	{
		for (j = 0; j < m - 1; j++)
		{
			if (t[i] > cpu[j])
			{
				cpu[j] = cpu[j + 1];
			}
			else 
			{
				break;
			}
		}
		cpu[j] = t[i];
		totalTime += cpu_run(cpu, m);
	}

	totalTime += cpu[m - 1];

	printf("%d\n", totalTime);

	return 0;
}
