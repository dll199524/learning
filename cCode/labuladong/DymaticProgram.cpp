#include <vector>

using namespace std;

int main() {

}

int fib(int n) 
{
    if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

//备忘录
int fibMemory(int n) 
{
    if (n < 1) return 0;
    vector<int> memo(n + 1, 0);
    return helper(memo, n);
}
int helper(vector<int> memo, int n) 
{
    if (n == 1 || n == 2) return 1;
    if (memo[n] != 0) return memo[n];
    memo[n] = helper(memo, n - 1) + helper(memo, n - 2);
    return memo[n];
}

//自底向上
int fibUp(int n) 
{
    vector<int> dp(n + 1, 0);
    dp[1] = dp[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        dp[n] = dp[n - 1] + dp[n - 2];
    }
    return dp[n];
}

int fib(int n) 
{
    if (n == 1 || n == 2) return 1;
    int pre = 1, cur = 1;
    for (int i = 3; i <= n; i++)
    {
        int sum = pre + cur;
        pre = cur;
        cur = sum;
    }
    return cur;   
}

int coinchange(vector<int>& coins, int amount) 
{
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 0; i < amount + 1; i++)
    {
        for (int coin : coins) {
            if (i - coin < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i -coin]);
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
}