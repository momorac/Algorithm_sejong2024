#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int MAX = 30;
int A[30];
int H[30];
int *m;

// airtel Divide and Conquer
int airtelDC(int n, int s, int d)
{
    if (s == d)
        return 0;
    int min_cost = 999999;
    for (int i = s; i < d; i++)
    {
        int cost = airtelDC(n, s, i) + H[i] + A[d - i];
        min_cost = min_cost < cost ? min_cost : cost;
    }
    return min_cost;
}

// airtel Dynamic Programming
int airtelDP(int n, int s, int d)
{
    m = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        m[i] = 999999; // 초기화
    m[s] = 0;

    for (int i = s + 1; i <= d; i++)
    {
        for (int j = s; j < i; j++)
        {
            int cost = m[j] + H[j] + A[i - j];
            m[i] = m[i] < cost ? m[i] : cost;
        }
    }
    int result = m[d];
    free(m);
    return result;
}

int main()
{
    int n, s, d, mincost;
    int sd[3][2] = {{0, 4}, {2, 5}, {2, 4}};
    clock_t S, E;

    // 배열 초기화
    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    }

    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++)
    {
        H[i] = (H[i - 1] + i) % 9 + 1;
    }

    printf("  n  s  d   mincost  version   cputime\n");

    // 테스트 실행 (n = 6)
    n = 6;
    for (int i = 0; i < 3; i++)
    {
        s = sd[i][0];
        d = sd[i][1];

        // airtelDC 실행
        S = clock();
        mincost = airtelDC(n, s, d);
        E = clock();
        double cpu_time = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
        printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", cpu_time);

        // airtelDP 실행
        S = clock();
        mincost = airtelDP(n, s, d);
        E = clock();
        cpu_time = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
        printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", cpu_time);
    }

    // 본 실행 (n = MAX)
    n = MAX;
    s = 1;
    d = n - 2;

    // airtelDC 실행
    S = clock();
    mincost = airtelDC(n, s, d);
    E = clock();
    double cpu_time = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
    printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", cpu_time);

    // airtelDP 실행
    S = clock();
    mincost = airtelDP(n, s, d);
    E = clock();
    cpu_time = ((double)(E - S)) / CLOCKS_PER_SEC * 1000;
    printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", cpu_time);

    return 0;
}
