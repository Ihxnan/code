#include <ihxnan>

struct HLD {
    int n, cur;
    vi fa, sz, dep, in, out, seq, top;
    vvi adj;
    HLD(int n)
        : n(n), cur(1), fa(n + 1), sz(n + 1), dep(n + 1), in(n + 1), out(n + 1), seq(n + 1), top(n + 1), adj(n + 1)
    {
    }

    void add(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs1(int u)
    {
        if (fa[u])
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        sz[u] = 1;
        for (auto &v : adj[u])
        {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    }

    void dfs2(int u)
    {
        seq[in[u] = cur++] = u;
        for (auto &v : adj[u])
        {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }

    void work()
    {
        top[1] = 1;
        dfs1(1);
        dfs2(1);
    }

    int lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        return u;
    }

    int dist(int u, int v)
    {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    bool query(int u, int v, int x)
    {
        return dist(x, u) + dist(x, v) == dist(u, v);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        hld.add(u, v);
    }
    hld.work();

    for (int i = 0, a, b, c, d, r, s; i < q; ++i)
    {
        cin >> a >> b >> c >> d;
        r = hld.lca(a, b), s = hld.lca(c, d);
        cout << (hld.query(a, b, s) || hld.query(c, d, r) ? "Y" : "N") << endl;
    }
}
