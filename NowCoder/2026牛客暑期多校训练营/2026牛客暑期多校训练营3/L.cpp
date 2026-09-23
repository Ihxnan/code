#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m;
    cin >> n >> m;
    vvi mp(n + 1, vi(m + 1)), sta(mp);
    vector<pii> arr;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j], arr.emplace_back(i, j);
    sort(arr.begin(), arr.end(), [&](auto &a, auto &b) { return mp[a.first][a.second] > mp[b.first][b.second]; });
    gdb(arr);

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (auto &[x, y] : arr)
    {
        int flag = 0;
        for (int i = 0; i < 4; ++i)
        {
            int a = x + dx[i];
            int b = y + dy[i];
            if (a < 1 || a > n || b < 1 || b > m || mp[x][y] >= mp[a][b])
                continue;
            if (!sta[a][b])
                flag = 1;
        }
        sta[x][y] = flag;
    }

    gdb(sta);

    int q;
    cin >> q;
    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;
        cout << (sta[x][y] ? "First" : "Second") << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
