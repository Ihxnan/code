#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;

    vector<ll> l(n + 1), r(n + 1);
    for (int i = 1; i <= 2 * n; i++)
    {
        int x;
        cin >> x;
        if (!l[x])
            l[x] = i;
        r[x] = i;
    }

    vector<vector<pll>> e(2 * n + 1);
    for (int x = 1; x <= n; x++)
    {
        ll len = r[x] - l[x] + 1;
        e[r[x]].push_back({l[x], len * (len - 1)});
    }

    vl dp(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++)
    {
        dp[i] = dp[i - 1];
        for (auto &[L, w] : e[i])
            dp[i] = max(dp[i], w + dp[L - 1]);
    }

    cout << 2 * n + dp.back() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
