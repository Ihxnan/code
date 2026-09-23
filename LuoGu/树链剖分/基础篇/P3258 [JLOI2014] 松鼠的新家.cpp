#include <ihxnan>
#include <HLD>

void solve()
{
    int n;
    cin >> n;
    vi path(n);
    for (auto &p : path)
        cin >> p;
    HLD hld(n);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        hld.add(u, v);
    }
    hld.work();
    vi sum(n + 1);
    for (int i = 1, r; i < n; ++i)
    {
        r = hld.lca(path[i], path[i - 1]);
        ++sum[hld.fa[path[i]]], ++sum[path[i - 1]];
        --sum[r], --sum[hld.fa[r]];
    }
    for (int i = n, t; t = hld.seq[i], i >= 1; --i)
        sum[hld.fa[t]] += sum[t];
    for (int i = 1; i <= n; ++i)
        cout << sum[i] << endl;
}
