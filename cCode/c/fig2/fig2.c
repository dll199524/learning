#include <stdio.h>

//复杂度分析
#define NlogNAlgorithm
#define ElementType int
#define NotFound (-1)
#define isEven(N) ((N) % 2 == 0)

/**
 * n的三次方 注意里面有三个for循环
 * 最大子序列的和的不同解法
**/
#ifdef CubicAlgorithm

int MaxSubsequenceSum(const int A[], int N)
{
    int ThisSum, MaxSum, i, j, k;
    Maxsum = 0;
    for (i = 0; i < N; i++)
    {
        for (j = i; j < N; j++)
        {
            ThisSum = 0; //注意
            for (k = i; k < N; k++)
                ThisSum += A[k];
            if (ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }
    return MaxSum;
}

#endif

//n的平方 注意里面有两个个for循环
#ifdef QuadraticAlgorithm

int MaxSubsequenceSum(const int A[], int N)
{
    int ThisSum, MaxSum, i, j;
    MaxSum = 0;
    for (i = 0; i < N; i++)
    {
        ThisSum = 0; //注意
        for (j = i; j < N; j++)
        {
            ThisSum += A[j];
            if (ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }
    return MaxSum;
}

#endif

//nlogn 注意里面采用了二分法
#ifdef NlogNAlgorithm

static int Max3(int A, int B, int C)
{
    return A > B ? A > C ? A : C : B > C ? B
                                         : C;
}

static int MaxSum(const int A[], int left, int right)
{
    int MaxLeftSum, MaxRightSum;
    int MaxLeftBorderSum, MaxRightBorderSum;
    int LeftBorderSum, RightBorderSum;
    int center, i;

    if (left == right)
        if (A[left] > 0)
            return left;
        else
            return 0;
    center = (left + right) / 2;
    MaxLeftSum = MaxSum(A, left, center);
    MaxRightSum = MaxSum(A, center + 1, right);

    MaxLeftBorderSum = 0, LeftBorderSum = 0;
    for (i = center; i >= left; i--)
    {
        LeftBorderSum += A[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }

    MaxRightBorderSum = 0, RightBorderSum = 0;
    for (i = center + 1; i <= right; i++)
    {
        RightBorderSum += A[i];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubsequenceSum(const int A[], int N)
{
    return MaxSum(A, 0, N - 1);
}

#endif

//n 一个for循环
#ifdef LinearAlgorithm

int MaxSubsequenceSum(const int A[], int N)
{
    int ThisSum, MaxSum, i;
    ThisSum = MaxSum = 0; //注意
    for (i = 0; i < N; i++)
    {
        ThisSum += A[i];
        if (ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}

#endif

/**
 * nlogn 注意里面采用了二分法 
 * 时间复杂度分析具体可参考 https://blog.csdn.net/oneby1314/article/details/107847693
 * ！！！二分查找这里必须为有序数组
**/
int BinarySearch(const ElementType A[], ElementType X, int N)
{
    int mid, low, high;
    low = 0;
    high = N - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (A[mid] < X)
            low = mid + 1;
        else if (A[mid] > X)
            high = mid - 1;
        else if (A[mid] == X)
            return mid;
    }
    return NotFound;
}

//欧几里得算法 logn
unsigned int Gcd(unsigned int m, unsigned int n)
{
    unsigned int rem;
    while (n > 0)
    {
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

//x的n次方
long int Pow(long int x, unsigned int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (isEven(n))
        return Pow(x * x, n / 2);
    else
        return Pow(x * x, n / 2) * x;
}

int main(int argc, char const *argv[])
{
    static int A[] = {4, -3, 5, -2, -1, 2, 6, -2};
    static int B[] = {1, 3, 5, 7, 9, 13, 15}; //有序数组
    printf("maxsum = %d", MaxSubsequenceSum(A, sizeof(A) / sizeof(A[0])));
    printf("\n%d", BinarySearch(B, 13, sizeof(B) / sizeof(B[0])));
    printf("\nGcd(45, 35) = %d\n", Gcd(45, 35));
    printf("Gcd(1989, 1590) = %d\n", Gcd(1989, 1590));
    printf("2 ^ 21 = %1d\n", Pow(2, 21));
    return 0;
}
