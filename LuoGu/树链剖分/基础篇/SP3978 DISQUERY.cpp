#include <ihxnan>

struct HLD {
    int n, cur;
    vi sz, fa, dep, top, in, out, seq;
    vvi adj;

    HLD(int n)
        : n(n), cur(1), sz(n + 1), fa(n + 1), dep(n + 1), top(n + 1), in(n + 1), out(n + 1), seq(n + 1), adj(n + 1)
    {
    }

    void add(int u, int v)
    {
        adj[u].push_back(v), adj[v].push_back(u);
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
        in[u] = cur++;
        seq[in[u]] = u;
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

    bool isAncestor(int u, int v)
    {
        return in[u] <= in[v] && in[v] < out[u];
    }
};

void solve()
{
    int n;
    cin >> n;
    HLD hld(n);
    vector<ti> edges(n - 1);
    for (auto &[u, v, w] : edges)
        cin >> u >> v >> w, hld.add(u, v);
    hld.work();

    vi arr(n + 1);
    for (auto &[u, v, w] : edges)
    {
        if (hld.isAncestor(v, u))
            swap(u, v);
        arr[hld.in[v]] = w;
    }

    int len = __lg(n) + 1;
    vvi mi_st(len, vi(n + 1));

    for (int i = 1; i <= n; ++i)
        mi_st[0][i] = arr[i];

    vvi ma_st(mi_st);

    for (int i = 1; i < len; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
        {
            mi_st[i][j] = min(mi_st[i - 1][j], mi_st[i - 1][j + (1 << i - 1)]);
            ma_st[i][j] = max(ma_st[i - 1][j], ma_st[i - 1][j + (1 << i - 1)]);
        }

    auto query = [&](int l, int r) -> pii {
        int k = __lg(r - l + 1);
        return {min(mi_st[k][l], mi_st[k][r - (1 << k) + 1]), max(ma_st[k][l], ma_st[k][r - (1 << k) + 1])};
    };

    auto work = [&](pii &a, pii b) -> void {
        a.first = min(a.first, b.first);
        a.second = max(a.second, b.second);
    };

    auto &fa = hld.fa;
    auto &in = hld.in;
    auto &top = hld.top;
    auto &dep = hld.dep;
    auto qry = [&](int u, int v) -> pii {
        pii ans{iINF, -iINF};
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            work(ans, query(in[top[u]], in[u]));
            u = fa[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        if (in[u] < in[v])
            work(ans, query(in[u] + 1, in[v]));
        return ans;
    };

    int q;
    cin >> q;
    pii ans;
    for (int i = 0, u, v; i < q; ++i)
    {
        cin >> u >> v;
        ans = qry(u, v);
        cout << ans.first << ' ' << ans.second << endl;
    }
}
