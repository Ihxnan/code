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
    vector<string> mp(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> mp[i], mp[i] = '^' + mp[i];

    int color = 0;
    vi memo(n * m + 1);
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    vvi sta(n + 1, vi(m + 1));

    auto dfs = [&](auto &&self, int x, int y, int color) -> int {
        int ans = 0;
        for (int i = 0; i < 4; ++i)
        {
            int a = x + dx[i];
            int b = y + dy[i];
            if (a < 1 || a > n || b < 1 || b > m || sta[a][b])
                continue;
            if (mp[a][b] == '*')
                ++ans;
            else
                ans += self(self, a, b, sta[a][b] = color);
        }
        return ans;
    };

    for (int i = 0, x, y; i < k; ++i)
    {
        cin >> x >> y;
        if (sta[x][y])
            cout << memo[sta[x][y]] << endl;
        else
            cout << (memo[sta[x][y]] = dfs(dfs, x, y, sta[x][y] = ++color)) << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
