#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <DSU>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, q;
    cin >> n >> q;
    vi fa(n + 1);
    for (int i = 2; i <= n; ++i)
        cin >> fa[i];
    vvi adj(n + 1);
    for (int i = 0, u, v; i < q; ++i)
        cin >> u >> v, adj[v].push_back(u);

    DSU dsu(n);
    ll ans = 0;
    for (int i = n; i >= 2; --i)
    {
        for (auto &p : adj[i])
            dsu.merge(p, i);
        ans += dsu.size(i);
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
