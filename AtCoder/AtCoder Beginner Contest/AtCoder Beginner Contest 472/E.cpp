#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<set<int>> adj(n + 1);
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    vi v(n + 1);
    int oy = 0;
    vi dep(n + 1), dfn{0};
    auto dfs = [&](auto &&self, int x, int color) -> void {
        if (oy)
            return;
        v[x] = color;
        dfn.push_back(x);
        for (auto &y : adj[x])
            if (!v[y])
                dep[y] = dep[x] + 1, self(self, y, 3 - color);
            else if (v[y] == color)
                return oy = y, void();
    };
    dfs(dfs, 1, 1);
    if (!oy)
        return cout << -1 << endl, void();
    vi circle{oy};
    while (true)
    {
        while (dep[dfn.back()] >= dep[circle.back()])
            dfn.pop_back();
        circle.push_back(dfn.back());
        if (v[oy] == v[circle.back()] && adj[circle.back()].count(oy))
            break;
    }
    cout << circle.size() << endl;
    for (auto &p : circle)
        cout << p << ' ';
    cout << endl;
}
