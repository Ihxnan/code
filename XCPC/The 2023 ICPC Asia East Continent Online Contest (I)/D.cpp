#include <ihxnan>
#define int long long

struct DSU {
    vector<ll> fa, sz, cnt;

    DSU(int n) : fa(n + 1), sz(n + 1, 1), cnt(n + 1)
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
        ++cnt[get(x)];
        if ((x = get(x)) == (y = get(y)))
            return false;
        fa[y] = x;
        cnt[x] += cnt[y];
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

void solve()
{
    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        dsu.merge(u, v);
    }

    vi arr;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        if (i == dsu.get(i))
            ans += dsu.size(i) * (dsu.size(i) - 1) / 2 - dsu.cnt[dsu.get(i)], arr.push_back(i);

    sort(arr.begin(), arr.end(), [&](int x, int y) { return dsu.size(x) < dsu.size(y); });

    if (!ans)
        ans += (dsu.size(arr[0]) + dsu.size(arr[1])) * (dsu.size(arr[0]) + dsu.size(arr[1]) - 1) / 2 - dsu.cnt[arr[0]] -
               dsu.cnt[arr[1]];

    cout << ans << endl;
}
