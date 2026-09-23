#include <ihxnan>
#include <Comb>

#define mod 59393
Comb comb(mod);

ll lucas(int x, int y)
{
    if (y == 0)
        return 1;
    return lucas(x / mod, y / mod) * comb.C(x % mod, y % mod) % mod;
}

ll get(int sx, int sy, int ex, int ey)
{
    int n = ex - sx, m = ey - sy;
    if (min(n, m) < 0)
        return 0;
    ll res = 0;
    int ub = min(n, m);
    for (int i = 0; i <= ub; i++)
        res = (res + lucas(n + m - i, i) * lucas(n + m - i * 2, n - i) % mod) % mod;
    return res;
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    ++n, ++m;
    vector<pii> p(k);
    for (auto &[x, y] : p)
        cin >> x >> y;
    ++k;
    p.emplace_back(1, 1);
    p.emplace_back(n, m);
    sort(p.begin(), p.end());

    vvl f(k + 1, vl(k + 1));
    for (int i = 0; i <= k; i++)
        for (int j = i + 1; j <= k; j++)
            f[i][j] = get(p[i].first, p[i].second, p[j].first, p[j].second);

    auto calc = [&](int s) -> int {
        if (!(s & 1 << 0) || !(s & 1 << k))
            return 0;
        int lst[22] = {}, cnt = 0, times = 1;
        for (int i = 0; i <= k; i++)
            if (s & 1 << i)
            {
                lst[++cnt] = i;
                times = times * -1;
            }
        times = (times + mod) % mod;
        for (int i = 2; i <= cnt; i++)
            times = times * f[lst[i - 1]][lst[i]] % mod;
        return times;
    };

    ll ans = 0;
    for (int i = 0; i < 1 << k + 1; i++)
        ans = (ans + calc(i)) % mod;

    cout << ans << endl;
}
