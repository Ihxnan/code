#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
struct DSU
{
    vector<int> fa, sz, ma;

    DSU(int n) : fa(n + 1), sz(n + 1, 1), ma(n + 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }

    int get(int x)
    {
        if (fa[x] == x)
            return x;
        int rt = get(fa[x]);
        ma[x] = max(ma[x], ma[fa[x]]);
        return fa[x] = rt;
    }

    bool merge(int x, int y, int v)
    {
        if ((x = get(x)) == (y = get(y)))
            return false;
        fa[x] = y;
        sz[y] += sz[x];
        ma[x] = max(v - sz[x] + 1, ma[y]);
        return true;
    }

    bool same(int x, int y)
    {
        return get(x) == get(y);
    }

    int size(int x)
    {
        return sz[get(x)];
    }
};
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    DSU dsu(fid(n + 1, m + 1));
    vvi mp(n + 2, vi(m + 2));

    int ans = 0;
    for (int i = 0, op, x, y; i < q; ++i)
    {
        cin >> op >> x >> y;
        x ^= ans, y ^= ans;
        if (op == 1)
        {
            cin >> mp[x][y];
            if (mp[x - 1][y])
                dsu.merge(fid(x - 1, y), fid(x, y), mp[x][y]);
            if (mp[x + 1][y])
                dsu.merge(fid(x + 1, y), fid(x, y), mp[x][y]);
            if (mp[x][y - 1])
                dsu.merge(fid(x, y - 1), fid(x, y), mp[x][y]);
            if (mp[x][y + 1])
                dsu.merge(fid(x, y + 1), fid(x, y), mp[x][y]);
            cout << (ans = dsu.size(fid(x, y)) - 1) << endl;
        }
        else
        {
            dsu.get(fid(x, y));
            cout << (ans = max(dsu.ma[fid(x, y)] - mp[x][y], 0)) << endl;
        }
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
