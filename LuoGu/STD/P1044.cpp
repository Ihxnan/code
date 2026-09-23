#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
int dp[20][20];
int dfs(int sin, int sa)
{
    if (dp[sin][sa])
        return dp[sin][sa];
    if (sin == 0 && sa == 0)
        return dp[sin][sa] = 1;

    int ans = 0;
    if (sin)
        ans += dfs(sin - 1, sa + 1);

    if (sa)
        ans += dfs(sin, sa - 1);

    return dp[sin][sa] = ans;
}

void solve()
{
    int n;
    cin >> n;
    cout << dfs(n, 0) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
