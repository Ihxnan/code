#include <ihxnan>

int init = [] { return cin >> t, 0; }();

struct HLD {
    int n, cur, len;
    vl sz, c, dep, in, out, seq;
    vvl adj, st, fa;

    HLD(int n)
        : n(n), cur(1), len(__lg(n) + 1), sz(n + 1), c(n + 1), dep(n + 1), in(n + 1), out(n + 1), seq(n + 1), adj(n + 1)
    {
        st.resize(len, vl(n + 1));
        fa.resize(len, vl(n + 1));
        rd1(c);
        for (int i = 0, u, v; i < n - 1; ++i)
            cin >> u >> v, add(u, v);
        update(1);
        work();
    }

    void update(int u)
    {
        if (fa[0][u])
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[0][u]));

        for (auto &v : adj[u])
            fa[0][v] = u, update(v);

        if (adj[u].size())
        {
            sort(adj[u].begin(), adj[u].end(), [&](int x, int y) { return c[x] < c[y]; });
            c[u] = min(c[u], c[adj[u][0]] + c[adj[u][1]]);
        }
    }

    void add(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 1)
    {
        dep[root] = 0;
        fa[0][root] = 0;
        dfs1(root);
        dfs2(root);
    }

    void dfs1(int u)
    {
        sz[u] = 1;
        for (int i = 1; 1 << i <= dep[u]; ++i)
            fa[i][u] = fa[i - 1][fa[i - 1][u]], st[i][u] = st[i - 1][u] + st[i - 1][fa[i - 1][u]];
        for (auto &v : adj[u])
        {
            st[0][v] = v == adj[u][0] ? c[adj[u][1]] : c[adj[u][0]];
            dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
        }
    }

    void dfs2(int u)
    {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto &v : adj[u])
            dfs2(v);
        out[u] = cur;
    }

    bool isAncesto(int u, int v)
    {
        return in[u] <= in[v] && in[v] < out[u];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    HLD hld(n);

    for (int i = 0, x, y; i < m; ++i)
    {
        cin >> x >> y;
        if (hld.isAncesto(y, x) == false)
            cout << -1 << endl;
        else
        {
            ll ans = 0;
            int dist = hld.dep[x] - hld.dep[y];
            for (int i = 0; dist >> i > 0; ++i)
                if (dist >> i & 1)
                {
                    dist -= 1 << i;
                    ans += hld.st[i][x];
                    x = hld.fa[i][x];
                }
            cout << ans << endl;
        }
    }
}
