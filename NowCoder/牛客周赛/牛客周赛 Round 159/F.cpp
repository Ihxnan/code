#include <ihxnan>
#include <HLD>

ll qmi(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1)
            res = res * a % MOD;
    return res;
}

template <typename T> struct Fenwick {
    int n;
    vector<T> tree;

    Fenwick(int n) : n(n), tree(n + 1)
    {
    }

    void add(int x, const T &v)
    {
        for (; x <= n; x += x & -x)
            tree[x] = (tree[x] + v + MOD) % MOD;
    }

    T query(int x)
    {
        T ans{};
        for (; x > 0; x -= x & -x)
            ans = (ans + tree[x]) % MOD;
        return ans;
    }

    T query(int l, int r)
    {
        return (query(r) - query(l - 1) + MOD) % MOD;
    }
};

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    HLD hld(n);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();
    Fenwick<ll> fenwick(n);
    auto &dep = hld.dep, &in = hld.in, &fa = hld.fa, &top = hld.top;
    for (int i = 1; i <= n; ++i)
        if (str[i - 1] == '1')
            fenwick.add(in[i], qmi(2, dep[i]));

    auto query = [&](int u, int v) -> ll {
        ll res = 0;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = (res + fenwick.query(in[top[u]], in[u])) % MOD;
            u = fa[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        return (res + fenwick.query(in[u], in[v])) % MOD;
    };

    char op;
    for (int i = 0, t; i < q; ++i)
    {
        cin >> op >> t;
        if (op == 'F')
        {
            if (str[t - 1] == '1')
                fenwick.add(in[t], -qmi(2, dep[t]));
            else
                fenwick.add(in[t], qmi(2, dep[t]));
            str[t - 1] ^= 1;
        }
        else
            cout << query(1, t) << endl;
    }
}
