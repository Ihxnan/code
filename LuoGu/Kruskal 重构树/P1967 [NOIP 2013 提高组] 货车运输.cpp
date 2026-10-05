#include <ihxnan>
#include <DSU>
#include <HLD>

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ti> edges(m);
    for (auto &[x, y, z] : edges)
        cin >> x >> y >> z;
    sort(edges.begin(), edges.end(), [&](auto &x, auto &y) { return get<2>(x) > get<2>(y); });

    DSU dsu(2 * n + 1);
    HLD hld(2 * n + 1);
    int cur = n + 1;
    vi weight(2 * n + 1);
    for (auto &[x, y, z] : edges)
        if (!dsu.same(x, y))
        {
            weight[cur] = z;
            hld.add(cur, dsu.get(x));
            hld.add(cur, dsu.get(y));
            dsu.merge(cur, x);
            dsu.merge(cur, y);
            ++cur;
        }

    for (int i = 1; i < cur; ++i)
        if (i == dsu.get(i))
            hld.add(cur, i);

    hld.work(cur);

    int q;
    cin >> q;
    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;
        if (dsu.same(x, y))
            cout << weight[hld.lca(x, y)] << endl;
        else
            cout << -1 << endl;
    }
}
