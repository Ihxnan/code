#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    ll ans = 0;
    vector<vvi> mp(n + 2, vvi(n + 2, vi(n + 2)));
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 1; j <= n + 1; ++j)
            for (int k = 1; k <= n + 1; ++k)
            {
                cin >> mp[i][j][k];
                if (i == j && i == k)
                    ans += mp[i][j][k];
                if (i == j && i + k == n + 2)
                    ans += mp[i][j][k];
                if (i == k && i + j == n + 2)
                    ans += mp[i][j][k];
                if (j == k && i + j == n + 2)
                    ans += mp[i][j][k];
            }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
