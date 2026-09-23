#include <ihxnan>
#include <DSU>
#include <HLD>

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int, int>> edges(m);
    int t = 0;
    for (auto &[u, v, w, id] : edges)
        cin >> u >> v >> w, id = t++;
    sort(edges.begin(), edges.end(), [&edges](auto &a, auto &b) { return get<2>(a) < get<2>(b); });

    gdb(edges);

    t = 0;
    vb sta(m);
    DSU dsu(n);
    HLD hld(n);
    ll sum = 0;
    for (auto &[u, v, w, id] : edges)
    {
        if (!dsu.same(u, v))
        {
            sum += w;
            sta[t] = true;
            hld.add(u, v);
            dsu.merge(u, v);
        }
        ++t;
    }
    hld.work();

    gdb(sum);
    gdb(sta);

    auto &in = hld.in;
    int len = __lg(n) + 1;
    vvi st(len, vi(n + 1));
    for (int i = 0; i < m; ++i)
        if (sta[i])
        {
            auto &[u, v, w, id] = edges[i];
            if (hld.isAncester(v, u))
                swap(u, v);
            st[0][in[v]] = w;
        }

    for (int i = 1; i < len; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);

    auto qry = [&](int l, int r) -> int {
        int k = __lg(r - l + 1);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    };

    auto &top = hld.top, &fa = hld.fa, &dep = hld.dep;
    auto query = [&](int u, int v) -> int {
        int res = 0;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = max(res, qry(in[top[u]], in[u]));
            u = fa[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        if (in[u] < in[v])
            res = max(res, qry(in[u] + 1, in[v]));
        return res;
    };

    t = 0;
    vl ans(m);
    for (auto &[u, v, w, id] : edges)
        if (sta[t++])
            ans[id] = sum;
        else
            ans[id] = sum + w - query(u, v);

    for (auto &p : ans)
        cout << p << endl;
}

