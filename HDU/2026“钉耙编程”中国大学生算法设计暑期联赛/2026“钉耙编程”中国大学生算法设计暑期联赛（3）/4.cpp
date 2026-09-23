#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <MinCostFlow>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
MinCostFlow<ll> mcf;
void solve()
{
    int n, m;
    cin >> n >> m;
    mcf.init(n + m + 2);
    for (int i = 1; i <= n; ++i)
        mcf.add(0, i, 1, 0);
    for (int i = 1, k; i <= n; ++i)
    {
        cin >> k;
        for (int j = 0, t; j < k; ++j)
            cin >> t, mcf.add(i, n + t, 1, 0);
    }
    for (int i = 1, k; i <= m; ++i)
    {
        cin >> k;
        for (int j = 0, t; j < k; ++j)
            cin >> t, mcf.add(n + i, n + m + 1, 1, t);
    }
    cout << mcf.flow(0, n + m + 1).second << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
