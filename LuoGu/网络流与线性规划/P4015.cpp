#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <MaxCostFlow>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int m, n;
    cin >> m >> n;

    MaxCostFlow<int> micf(m + n + 2);
    MaxCostFlow<int> macf(m + n + 2);

    for (int i = 1, t; i <= m; ++i)
        cin >> t, micf.add(0, i, t, 0), macf.add(0, i, t, 0);

    for (int i = m + 1, t; i <= m + n; ++i)
        cin >> t, micf.add(i, n + m + 1, t, 0), macf.add(i, n + m + 1, t, 0);

    for (int i = 1, t; i <= m; ++i)
        for (int j = m + 1; j <= m + n; ++j)
            cin >> t, micf.add(i, j, iINF, -t), macf.add(i, j, iINF, t);

    cout << -micf.flow(0, n + m + 1).second << endl << macf.flow(0, n + m + 1).second << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
