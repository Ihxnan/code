#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    string str;
    cin >> str;
    int n = str.size();

    if (n < 3)
        return cout << 1 << endl, void();

    str = '^' + str;
    vector<vvl> dp(n + 1, vvl(2, vl(3)));

    dp[1][str[1] - '0'][2] = 1;
    dp[2][str[2] - '0'][str[1] - '0'] = 1;

    for (int i = 3; i <= n; ++i)
    {
        ll sum = 0;
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 3; ++k)
                sum += dp[i - 2][j][k];

        if (str[i] == '0' && str[i - 1] == '0')
        {
            dp[i][0][0] += dp[i - 2][1][0] + sum;
            dp[i][0][1] += dp[i - 2][1][1];
            dp[i][0][2] += dp[i - 2][1][2];
        }
        if (str[i] == '0' && str[i - 1] == '1')
        {
            dp[i][0][1] += sum;
            dp[i][1][0] += dp[i - 2][1][0];
            dp[i][1][1] += dp[i - 2][1][1];
            dp[i][1][2] += dp[i - 2][1][2];
        }
        if (str[i] == '1' && str[i - 1] == '0')
        {
            dp[i][1][0] += sum;
            dp[i][0][0] += dp[i - 2][0][0];
            dp[i][0][1] += dp[i - 2][0][1];
            dp[i][0][2] += dp[i - 2][0][2];
        }
        if (str[i] == '1' && str[i - 1] == '1')
        {
            dp[i][1][0] += dp[i - 2][0][0];
            dp[i][1][1] += dp[i - 2][0][1] + sum;
            dp[i][1][2] += dp[i - 2][0][2];
        }

        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 3; ++k)
                dp[i][j][k] %= mod;
    }

    ll ans = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            ans += dp[n][i][j];
    gdb(dp);
    cout << ans % mod << endl;
}
