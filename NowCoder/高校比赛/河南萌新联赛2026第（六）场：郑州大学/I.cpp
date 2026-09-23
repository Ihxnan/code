#include <ihxnan>

void solve()
{
    int n, m, a, q;
    cin >> n >> m >> a >> q;
    vvi mp(n + 2, vi(m + 2));
    vi left, right;
    for (int i = -a; i <= a; ++i)
    {
        int delta = sqrt(a * a - i * i);
        left.push_back(-delta);
        right.push_back(delta);
    }

    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;
        for (int j = -a, id = 0, l, r; j <= a; ++j, ++id)
            if (y + j >= 1 && y + j <= m)
            {
                l = max(1, x + left[id]), r = min(n, x + right[id]);
                ++mp[l][y + j], --mp[r + 1][y + j];
            }
    }

    for (int y = 1; y <= m; ++y)
        for (int x = 1; x <= n; ++x)
            mp[x][y] += mp[x - 1][y];

    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cnt += mp[i][j] > 0;

    cout << cnt << endl;
}
