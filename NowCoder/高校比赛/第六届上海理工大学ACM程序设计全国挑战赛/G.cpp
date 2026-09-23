#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<set<int>> arr(m);
    for (int i = 0, k; i < m; ++i)
    {
        cin >> k;
        for (int j = 0, t; j < k; ++j)
            cin >> t, arr[i].insert(t);
    }
    gdb(arr);
    for (int i = 0, u, v; i < q; ++i)
    {
        cin >> u >> v;
        int cnt = 0;
        for (auto &p : arr)
            cnt += p.count(u) && p.count(v);
        cout << cnt << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
