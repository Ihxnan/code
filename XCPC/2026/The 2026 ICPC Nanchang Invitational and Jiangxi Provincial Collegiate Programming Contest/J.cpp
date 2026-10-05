#include <ihxnan>
#include <DSU>
#include <HLD>

#define N 1000000

void solve()
{
    int n, q;
    cin >> n >> q;
    vi arr(n + 1);
    vi vis(N + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], vis[arr[i]] = 1;

    vi weight(2 * N);
    iota(weight.begin(), weight.end(), 0);

    vvi adj(N + 1);
    for (int i = N; i >= 1; --i)
        for (int j = i; j <= N; j += i)
            if (vis[j])
                adj[i].push_back(j);

    DSU dsu(2 * N);
    HLD hld(2 * N);
    int cur = N + 1;

    for (int i = N; i >= 1; --i)
        for (int j = 1; j < adj[i].size(); ++j)
            if (!dsu.same(adj[i][j - 1], adj[i][j]))
            {
                weight[cur] = i;
                hld.add(cur, dsu.get(adj[i][j - 1]));
                hld.add(cur, dsu.get(adj[i][j]));
                dsu.merge(cur, adj[i][j - 1]);
                dsu.merge(cur, adj[i][j]);
                ++cur;
            }

    hld.work(--cur);

    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;
        cout << weight[hld.lca(arr[x], arr[y])] << endl;
    }
}
