#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    string color;
    cin >> n >> color;
    color = '^' + color;

    vvi tree(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    int root1 = 1;
    while (color[root1] != '1')
        ++root1;

    vi dist1(n + 1);
    int root2 = root1;
    auto dfs1 = [&](auto &&self, int fa, int root) -> void {
        for (auto &son : tree[root])
            if (son != fa)
            {
                dist1[son] = dist1[root] + 1;
                if (color[son] == '1' && dist1[son] > dist1[root2])
                    root2 = son;
                self(self, root, son);
            }
    };
    dfs1(dfs1, 0, root1);

    root1 = root2;
    fill(dist1.begin(), dist1.end(), 0);
    dfs1(dfs1, 0, root1);

    vi dist2(n + 1);
    auto dfs2 = [&](auto &&self, int fa, int root) -> void {
        for (auto &son : tree[root])
            if (son != fa)
            {
                dist2[son] = dist2[root] + 1;
                self(self, root, son);
            }
    };
    dfs2(dfs2, 0, root2);

    for (int i = 1; i <= n; ++i)
        if (color[i] == '1')
            cout << dist1[root2] << endl;
        else
            cout << max({dist1[root2], dist1[i], dist2[i]}) << endl;
}
