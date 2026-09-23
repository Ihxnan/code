#include <ihxnan>

// 1: 1
// 2: 2
// 3: 3   2+1
// 4: 4   3+1
// 5: 5   4+1   3+2
// 6: 6   5+1   4+2  3+2+1

#define mod 19901014

ll dp[1001][1001];

int init = [] {
    for (int i = 0; i <= 1000; ++i)
        dp[i][0] = 1;
    for (int i = 1; i <= 1000; ++i)
        for (int j = 0; j <= 1000; ++j)
            if (j < i)
                dp[i][j] = dp[i - 1][j];
            else if (j >= i)
                dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - i]) % mod;
    return cin >> t, 0;
}();

void solve()
{
    int n;
    cin >> n;
    cout << dp[n][n] << endl;
}
