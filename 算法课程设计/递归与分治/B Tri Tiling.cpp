#include <ihxnan>

ll dp[31];
int init = [] {
    dp[0] = 1;
    for (int i = 2; i <= 30; i += 2)
    {
        dp[i] = dp[i - 2] * 3;
        for (int j = i - 4; j >= 0; j -= 2)
            dp[i] += dp[j] * 2;
    }
    return 0;
}();

void solve()
{
    int n;
    while (cin >> n, n != -1)
        cout << dp[n] << endl;
}
