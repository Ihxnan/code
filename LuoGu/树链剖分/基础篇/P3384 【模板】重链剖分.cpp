#include <ihxnan>
#include <HLD>
#include <SegmentTree>

void solve()
{
    ll n, m, r, p;
    cin >> n >> m >> r >> p;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    HLD hld(n);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work(r);

    auto &fa = hld.fa, &in = hld.in, &out = hld.out, &dep = hld.dep, &top = hld.top;

    SegmentTree<ll> segt(n);
    for (int i = 1; i <= n; ++i)
        segt.in[in[i]] = arr[i];
    segt.build();

    auto update1 = [&](int x, int y, int z) -> void {
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            segt.update(in[top[x]], in[x], z);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        segt.update(in[x], in[y], z);
    };

    auto query1 = [&](int x, int y) -> ll {
        ll res = 0;
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            res += segt.query(in[top[x]], in[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        res += segt.query(in[x], in[y]);
        return res;
    };

    auto update2 = [&](int x, int z) -> void { segt.update(in[x], out[x] - 1, z); };

    auto query2 = [&](int x) -> ll { return segt.query(in[x], out[x] - 1); };

    for (int i = 0, op, x, y, z; i < m; ++i)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y >> z;
            update1(x, y, z);
        }
        else if (op == 2)
        {
            cin >> x >> y;
            cout << query1(x, y) % p << endl;
        }
        else if (op == 3)
        {
            cin >> x >> z;
            update2(x, z);
        }
        else
        {
            cin >> x;
            cout << query2(x) % p << endl;
        }
    }
}
