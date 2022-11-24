#include <stdio.h>
#include <stdlib.h>

//第一章主要讲的是recursion 简单的递归
#define Error(Str) FatalError(Str)
#define FatalError(Str) fprint(stderr, "%s\n", Str), exit(1)
#define PrintDigit(Ch) (putchar((Ch) + '0'))

int F(int X) 
{
    if (X == 0) return 0;
    return 2 * F(X - 1) + X * X;
}

//错误的递归 unsigned int 无符号整形 大于等于0的数
int Bad(unsigned int N) 
{
    if (N == 0) return 0;
    return Bad(N / 3 + 1) + N - 1;
}

void PrintOut(unsigned int N) 
{
    if (N >= 10) PrintOut(N / 10);
    PrintDigit(N % 10);
}

int main(int argc, char const *argv[])
{
    printf("F(5) = %d\n", F(5));
    printf("Bad is infinite recursion\n");
    PrintOut(1369);
    putchar('\n');
    return 0;
}
