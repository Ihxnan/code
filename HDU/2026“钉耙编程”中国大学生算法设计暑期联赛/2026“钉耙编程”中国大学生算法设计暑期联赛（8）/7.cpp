#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    gdb(n, m, k, q);
    DSU dsu(n * m);
    vector<string> mp(n + 1);
    mp[0].resize(m + 1, '^');
    for (int i = 1; i <= n; ++i)
        cin >> mp[i], mp[i] = '^' + mp[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (mp[i][j] == '.')
            {
                if (mp[i][j - 1] == '.')
                    dsu.merge(fid(i, j), fid(i, j - 1));
                if (mp[i - 1][j] == '.')
                    dsu.merge(fid(i, j), fid(i - 1, j));
            }

    map<int, vi> adj;

    for (int i = 0, x1, y1, x2, y2; i < k; ++i)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        if (dsu.same(fid(x1, y1), fid(x2, y2)))
            continue;
        adj[dsu.get(fid(x1, y1))].push_back(dsu.get(fid(x2, y2)));
    }

    int cur;
    set<int> sta;
    map<int, set<int>> hash;

    auto dfs = [&](auto &&self, int r) -> void {
        for (auto &p : adj[r])
            if (!sta.count(p))
                sta.insert(p), self(self, p), hash[cur].insert(p);
    };

    for (auto &[k, v] : adj)
    {
        cur = k;
        sta.clear();
        sta.insert(k);
        dfs(dfs, k);
    }

    gdb(hash);

    for (int i = 0, x1, y1, x2, y2; i < q; ++i)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        if (dsu.same(fid(x1, y1), fid(x2, y2)) || hash[dsu.get(fid(x1, y1))].count(dsu.get(fid(x2, y2))))
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
}
