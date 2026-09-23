#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int>> arr(k + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0, t; j < m; ++j)
            cin >> t, arr[t].insert(j);
    for (int i = 1; i <= k; ++i)
        cout << arr[i].size() << ' ';
}
/* ╚══════════ /SOLVE ══════════╝ */
