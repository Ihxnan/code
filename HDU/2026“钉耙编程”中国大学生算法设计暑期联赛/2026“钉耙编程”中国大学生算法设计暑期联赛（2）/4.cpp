#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pii>> mp(n + 1);
    for (int i = 0, a, b, c; i < m; ++i)
    {
        cin >> a >> b >> c;
        mp[a].emplace_back(b, c);
    }
    for (int i = 1; i <= n; ++i)
    {
        reverse(mp[i].begin(), mp[i].end());
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
