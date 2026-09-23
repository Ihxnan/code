#include <ihxnan>

void solve()
{
    int n, l;
    cin >> n >> l;
    vi arr(n + 1);
    double sum = 0;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], sum += arr[i];
    sum /= n;

    vector<vector<vector<double>>> dp(l + 1, vector<vector<double>>(n + 1, vector<double>(n + 1)));

    for (int i = 1; i <= l; ++i)
        for (int j = 0; j <= n; ++j)
            dp[i][j][n - j] = j;

    auto lpair = [n](int j, int k) -> double { return n - k - j; };
    auto lcard = [n](int j, int k) -> double { return 2 * (n - k) - j; };

    for (int i = 1; i <= l; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = n - 1; k >= 0; --k)
            {
                if (j + 1 <= n && k - 1 >= 0 && lcard(j + 1, k - 1) >= 1)
                    dp[i][j][k] += (1 + dp[i][j - 1][k + 1]) * (j - 1) / lcard(j - 1, k + 1);

                if (k - 1 >= 0 && lpair(j, k - 1) >= 1 && lcard(j + 1, k - 1) >= 1)
                    dp[i][j][k] += (dp[i][j][k - 1] + 1) * lpair(j, k - 1) * 2 / lcard(j, k - 1) / lcard(j + 1, k - 1);

                if (i + 1 <= l && k - 1 >= 0 && lpair(j, k - 1) >= 1 && lcard(j + 1, k - 1) >= 1)
                    dp[i][j][k] +=
                        (dp[i + 1][j][k - 1] + 1) * 2 * lpair(j, k - 1) / lcard(j, k - 1) * j / lcard(j + 1, k - 1);

                if (i + 1 <= l && j - 2 >= 0 && lpair(j - 1, k) >= 1 && lcard(j - 1, k) >= 1)
                    dp[i][j][k] += dp[i + 1][j - 2][k] * 2 * lpair(j - 2, k) / lcard(j - 2, k) * 2 * lpair(j - 1, k) /
                                   lcard(j - 1, k);
            }

    printf("%.10f", sum * dp[l][0][0]);
}
