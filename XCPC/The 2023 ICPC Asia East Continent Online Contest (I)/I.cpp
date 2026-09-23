#include <ihxnan>

ll dp[100001][3][8];

void solve()
{
    string str;
    cin >> str;
    int n = str.size();
    str = '^' + str;
    for (int i = 1; i <= n; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            for (int j = 0; j < 8; ++j)
                if (j & 1)
                    dp[i][0][j] = dp[i - 1][0][7 ^ 1] + dp[i - 1][0] ;

            sta[i][0] |= 1;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][0] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 1) == 7)
                    dp[i][0] += dp[i - 1][j];
            }
        }

        if (str[i] >= 'a' && str[i] <= 'z')
        {
            sta[i][0] |= 1;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][0] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 1) == 7)
                    dp[i][0] += dp[i - 1][j];
            }

            sta[i][1] |= 2;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][1] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 2) == 7)
                    dp[i][1] += dp[i - 1][j];
            }
        }

        if (str[i] >= '0' && str[i] <= '9')
        {
            sta[i][2] |= 4;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][2] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 4) == 7)
                    dp[i][2] += dp[i - 1][j];
            }
        }

        if (str[i] == '?')
        {

            sta[i][0] |= 1;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][0] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 1) == 7)
                    dp[i][0] += dp[i - 1][j];
            }

            sta[i][1] |= 2;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][1] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 2) == 7)
                    dp[i][1] += dp[i - 1][j];
            }

            sta[i][2] |= 4;
            for (int j = 0; j < 3; ++j)
            {
                sta[i][2] |= sta[i - 1][j];
                if ((sta[i - 1][j] | 4) == 7)
                    dp[i][2] += dp[i - 1][j];
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < 3; ++i)
        ans += dp[n][i];

    cout << ans % mod;
}
