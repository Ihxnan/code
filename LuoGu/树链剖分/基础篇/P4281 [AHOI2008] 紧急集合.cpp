#include <ihxnan>
#include <HLD>

void solve()
{
    int n, m;
    cin >> n >> m;
    HLD hld(n);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();

    for (int i = 0, u, v, w; i < m; ++i)
    {
        cin >> u >> v >> w;
        int ans = 0, mi = iINF, r, d;
        r = hld.lca(u, v);
        d = hld.dist(r, w) + hld.dist(u, v);
        if (d < mi)
            mi = d, ans = r;

        r = hld.lca(u, w);
        d = hld.dist(r, v) + hld.dist(u, w);
        if (d < mi)
            mi = d, ans = r;

        r = hld.lca(w, v);
        d = hld.dist(r, u) + hld.dist(w, v);
        if (d < mi)
            mi = d, ans = r;

        cout << ans << ' ' << mi << endl;
    }
}
