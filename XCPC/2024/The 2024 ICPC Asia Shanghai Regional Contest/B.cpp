#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi mp(n + 1);
    vector<set<int>> adj(n + 1);
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    vi arr(n);
    for (auto &p : arr)
        cin >> p;

    int idx = 0;
    vb visited(n + 1);
    vector<pii> ans;

    auto dfs = [&](auto &&self, int u) -> void {
        if (idx >= n)
            return;

        ++idx;
        visited[u] = true;
        for (auto &p : mp[u])
            adj[p].erase(u);

        while (idx < n && adj[u].size())
        {
            while (idx < n && adj[u].count(arr[idx]))
                self(self, arr[idx]);

            if (idx < n && adj[u].size())
            {
                ans.emplace_back(u, arr[idx]);
                self(self, arr[idx]);
            }
        }
    };

    for (auto &p : arr)
        if (!visited[p])
            dfs(dfs, arr[idx]);

    cout << ans.size() << endl;
    for (auto &[a, b] : ans)
        cout << a << ' ' << b << endl;
}
