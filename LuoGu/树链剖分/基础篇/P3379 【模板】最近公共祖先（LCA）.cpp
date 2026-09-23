#include <ihxnan>
#include <HLD>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, r;
    cin >> n >> m >> r;
    HLD hld(n);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work(r);
    for (int i = 0, u, v; i < m; ++i)
        cin >> u >> v, cout << hld.lca(u, v) << endl;
}
