#include <ihxnan>
#include <DSU>

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mp(n + 2, vector<char>(m + 2));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j], mp[i][j] ^= 48;

    auto bfs4 = [&](vector<vector<char>> mp) -> pii {
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        DSU dsu(fid(n + 1, m + 1));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (mp[i][j])
                    for (int k = 0; k < 4; ++k)
                    {
                        int a = i + dx[k];
                        int b = j + dy[k];
                        if (mp[a][b])
                            dsu.merge(fid(i, j), fid(a, b));
                    }

        int cnt = 0, sz = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (mp[i][j])
                    cnt += fid(i, j) == dsu.get(fid(i, j)), sz = max(sz, dsu.size(fid(i, j)));

        return {cnt, sz};
    };

    auto bfs8 = [&](vector<vector<char>> mp) -> pii {
        DSU dsu(fid(n + 1, m + 1));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (mp[i][j])
                    for (int u = -1; u <= 1; ++u)
                        for (int v = -1; v <= 1; ++v)
                        {
                            int a = i + u;
                            int b = j + v;
                            if (mp[a][b])
                                dsu.merge(fid(i, j), fid(a, b));
                        }

        int cnt = 0, sz = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (mp[i][j])
                    cnt += fid(i, j) == dsu.get(fid(i, j)), sz = max(sz, dsu.size(fid(i, j)));

        return {cnt, sz};
    };

    auto [c4, s4] = bfs4(mp);
    auto [c8, s8] = bfs8(mp);

    cout << c4 - c8 << ' ' << s4 << ' ' << s8 << endl;
}
