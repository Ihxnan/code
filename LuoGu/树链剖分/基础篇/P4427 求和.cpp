#include <ihxnan>
#include <Comb>
#include <HLD>

// int init = [] { return cin >> t, 0; }();

Comb comb(mod);
void solve()
{
    int n;
    cin >> n;
    HLD hld(n);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();
    auto &fa = hld.fa;
    vvl sum(51, vl(n + 1));
    for (int i = 1; i <= 50; ++i)
    {
        for (int j = 1; j <= n; ++j)
            sum[i][j] = comb.qmi(hld.dep[j], i);
        for (int j = 1, t; j <= n; ++j)
        {
            t = hld.seq[j];
            sum[i][t] = (sum[i][t] + sum[i][fa[t]]) % mod;
        }
    }
    int m;
    cin >> m;
    for (int i = 0, u, v, w, r; i < m; ++i)
    {
        cin >> u >> v >> w;
        r = hld.lca(u, v);
        cout << ((sum[w][u] + sum[w][v] - sum[w][r] - sum[w][fa[r]]) % mod + mod) % mod << endl;
    }
}
