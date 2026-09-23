#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    if (k > (n - 1) / 2)
        return cout << 0, void();

    vvl dp(n + 1, vl(k + 1));
    for (ll i = 1, b = 1; i <= n; ++i, b = b * 2 % mod)
        dp[i][0] = b;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= min(k, (i - 1) / 2); ++j)
            dp[i][j] = (2 * (j + 1) * dp[i - 1][j] + (i - 2 * j) * dp[i - 1][j - 1]) % mod;

    cout << dp[n][k];
}
