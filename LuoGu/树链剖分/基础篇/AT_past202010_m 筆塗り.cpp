#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

struct HLD {
    int n, cur;
    vi fa, top, dep, in, out, seq, sz;
    vvi adj;

    HLD(int n)
        : n(n), cur(1), fa(n + 1), top(n + 1), dep(n + 1), in(n + 1), out(n + 1), seq(n + 1), sz(n + 1), adj(n + 1)
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

    bool isAncester(int u, int v)
    {
        return in[u] <= in[v] && in[v] < out[u];
    }
};

struct SegmentTree {
    int n;
    vi tree, tag;

    SegmentTree(int n) : n(n), tree(4 * n), tag(4 * n, -1)
    {
    }

    void change(int p, int l, int r, int c)
    {
        tree[p] = c;
        tag[p] = c;
    }

    void push_down(int p, int l, int r)
    {
        if (tag[p] != -1)
        {
            int mid = l + r >> 1;
            change(ls(p), l, mid, tag[p]);
            change(rs(p), mid + 1, r, tag[p]);
            tag[p] = -1;
        }
    }

    void update(int ul, int ur, int p, int l, int r, int c)
    {
        if (ul <= l && r <= ur)
            return change(p, l, r, c);
        push_down(p, l, r);
        int mid = l + r >> 1;
        if (ul <= mid)
            update(ul, ur, ls(p), l, mid, c);
        if (ur > mid)
            update(ul, ur, rs(p), mid + 1, r, c);
    }

    int query(int q, int p, int l, int r)
    {
        if (l == q && q == r)
            return tree[p];
        push_down(p, l, r);
        int mid = l + r >> 1;
        if (q <= mid)
            return query(q, ls(p), l, mid);
        return query(q, rs(p), mid + 1, r);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    vector<pii> edges(n - 1);
    for (auto &[u, v] : edges)
        cin >> u >> v, hld.add(u, v);
    hld.work();
    SegmentTree segt(n);

    auto &fa = hld.fa;
    auto &in = hld.in;
    auto &top = hld.top;
    auto &dep = hld.dep;
    auto update = [&](int ul, int ur, int c) -> void {
        while (top[ul] != top[ur])
        {
            if (dep[top[ul]] < dep[top[ur]])
                swap(ul, ur);
            segt.update(in[top[ul]], in[ul], 1, 1, n, c);
            ul = fa[top[ul]];
        }
        if (dep[ul] > dep[ur])
            swap(ul, ur);
        if (in[ul] < in[ur])
            segt.update(in[ul] + 1, in[ur], 1, 1, n, c);
    };

    for (int i = 0, u, v, c; i < q; ++i)
    {
        cin >> u >> v >> c;
        update(u, v, c);
    }

    for (auto &[u, v] : edges)
    {
        if (hld.isAncester(v, u))
            swap(u, v);
        cout << segt.query(in[v], 1, 1, n) << endl;
    }
}
