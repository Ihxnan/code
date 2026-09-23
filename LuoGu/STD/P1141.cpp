#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
int n, m;
map<int, int> memo;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int dfs(int x, int y, int flag, vector<string> &mp, vector<vector<int>> &sta)
{
    int ans = 1;
    sta[x][y] = flag;
    for (int i = 0; i < 4; ++i)
    {
        int a = x + dx[i];
        int b = y + dy[i];
        if (a < 1 || a > n || b < 1 || b > n || sta[a][b] || mp[a][b] == mp[x][y])
            continue;
        ans += dfs(a, b, flag, mp, sta);
    }
    return ans;
}

void solve()
{
    cin >> n >> m;

    vector<string> mp(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> mp[i], mp[i] = '^' + mp[i];

    vector<vector<int>> sta(n + 1, vector<int>(n + 1));

    int flag = 0;
    for (int i = 0, x, y; i < m; ++i)
    {
        cin >> x >> y;
        if (sta[x][y])
            cout << memo[sta[x][y]] << endl;
        else
            cout << (memo[flag] = dfs(x, y, ++flag, mp, sta)) << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
