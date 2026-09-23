#include <ihxnan>

struct DSU {
    vector<int> fa, sz;
    vector<vi> to;

    DSU(int n) : fa(n + 1), sz(n + 1, 1), to(n + 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }

    int get(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

    bool merge(int x, int y)
    {
        if ((x = get(x)) == (y = get(y)))
            return false;

        if (to[x].size() < to[y].size())
            swap(to[x], to[y]);

        while (to[y].size())
            to[x].push_back(to[y].back()), to[y].pop_back();

        fa[y] = x;
        sz[x] += sz[y];
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

ll qmi(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            res = res * a % mod;
    return res;
}

void solve()
{
    int n;
    cin >> n;

    vector<pii> choose(n - 1);
    for (auto &[a, b] : choose)
        cin >> a >> b;

    DSU dsu(n);

    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        dsu.to[u].push_back(v);
        dsu.to[v].push_back(u);
    }

    ll ans = 1;

    for (auto &[u, v] : choose)
    {
        u = dsu.get(u), v = dsu.get(v);

        if (u == v)
            return cout << 0 << endl, void();

        bool flag = true;

        if (dsu.to[u].size() > dsu.to[v].size())
            swap(u, v);

        for (auto &p : dsu.to[u])
            if (dsu.get(p) == v)
            {
                flag = false;
                break;
            }

        if (flag)
            return cout << 0 << endl, void();

        ans = ans * qmi(dsu.size(u), mod - 2) % mod * qmi(dsu.size(v), mod - 2) % mod;

        dsu.merge(u, v);
    }

    cout << ans << endl;
}
