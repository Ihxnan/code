#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int h, w, k;
    cin >> h >> w >> k;
    vector<vector<char>> mp(h + 1, vector<char>(w + 1));
    vb row(h + 1, true), col(w + 1, true);
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
        {
            cin >> mp[i][j];
            if (mp[i][j] == '#')
                row[i] = col[j] = false;
        }
    queue<pii> que;
    vvi sta(h + 1, vi(w + 1, -1));
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            if (row[i] && col[j])
                que.emplace(i, j), sta[i][j] = 0;
    int a, b;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    while (que.size())
    {
        auto [x, y] = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i)
        {
            a = x + dx[i];
            b = y + dy[i];
            if (a < 1 || a > h || b < 1 || b > w || mp[a][b] == '#' || sta[a][b] != -1)
                continue;
            sta[a][b] = sta[x][y] + 1;
            que.emplace(a, b);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            cnt += sta[i][j] != -1 && sta[i][j] <= k;
    cout << cnt << endl;
}
