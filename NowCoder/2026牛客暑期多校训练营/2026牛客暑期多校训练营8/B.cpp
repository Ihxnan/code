#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vb sta(2 * n);
    bool flag = false;
    for (int i = 0, t; i < m; ++i)
    {
        cin >> t;
        if (t >= 2 * n)
            flag = true;
        else
            sta[t] = true;
    }

    if (flag)
        return cout << 0 << endl, void();

    vvi dp(2 * n + 1, vi(n + 1));

    dp[0][0] = 1;

    for (int i = 1; i <= n * 2; ++i)
        for (int j = 0; j <= n; ++j)
        {
            if (j < n && !sta[i])
                dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
            if (j)
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
        }

    cout << dp[2 * n][0] << endl;
}
