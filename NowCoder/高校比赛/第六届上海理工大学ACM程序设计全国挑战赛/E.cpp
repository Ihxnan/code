#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cout
void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    int len = r - l + 1;

    vector<vector<double>> dp(2001, vector<double>(2001));
    vector<double> sum1(2001);
    double sum2;
    for (int i = 0; i <= 2000; ++i)
        for (int j = 0; j <= 2000; ++j)
        {

            double a = 0, b = 0;
            if (i)
                a = 1 - sum1[j] / len;

            if (j)
                b = 1 - sum2 / len;

            dp[i][j] = max(a, b);

            if (!i)
                sum1[j] = len * dp[0][j];

            if (!j)
                sum2 = len * dp[i][0];

            sum1[j] += dp[max(i - l + 1, 0)][j];
            sum1[j] -= dp[max(i - r, 0)][j];

            sum2 += dp[i][max(j - l + 1, 0)];
            sum2 -= dp[i][max(j - r, 0)];
        }

    vi arr(n);
    for (auto &p : arr)
        cin >> p;

    double ans = 0;
    for (int i = 0; i < n; ++i)
    {
        double t = 1;
        for (int j = 0; j < n; ++j)
            if (i != j)
                t = min(t, dp[arr[i]][arr[j]]);
        ans = max(ans, t);
    }

    cout << fixed << setprecision(9) << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
