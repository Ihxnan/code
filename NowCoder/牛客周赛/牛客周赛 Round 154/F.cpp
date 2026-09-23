#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
ll n, x, y;
int arr[2001];
ll dp[2001][51][51];

ll dfs(int pos, int a1, int a2)
{
    if (dp[pos][a1][a2] != lINF)
        return dp[pos][a1][a2];
    if (pos == 0)
        return dp[pos][a1][a2] = 0;
    int a0 = 0;
    if (pos >= 2)
        a0 = arr[pos - 2];
    for (int i = 0, b0, b1, b2; i <= 50; ++i)
        for (int j = 0; j <= 50; ++j)
        {
            b0 = max(0, a0 - i);
            b1 = max(0, a1 - 2 * i - j);
            b2 = max(0, a2 - i - 2 * j);
            dp[pos][a1][a2] = min(dp[pos][a1][a2], dfs(pos - 1, b0, b1) + (i + j) * y + b2 * x);
            if (b2 < 1)
                break;
        }
    return dp[pos][a1][a2];
};

void solve()
{
    cin >> n >> x >> y;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    memset(dp, 0x3f, sizeof dp);

    cout << dfs(n, arr[n - 1], arr[n]) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
