#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <MinCostFlow>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    MinCostFlow<int> mcf(n + 2);

    vi arr(n);
    int sum = 0;
    for (auto &p : arr)
        cin >> p, sum += p;
    sum /= n;

    for (int i = 0; i < n; ++i)
        if (arr[i] >= sum)
            mcf.add(n, i, arr[i] - sum, 0);
        else
            mcf.add(i, n + 1, sum - arr[i], 0);

    for (int i = 0; i < n; ++i)
        mcf.add(i, (i + 1) % n, iINF, 1), mcf.add(i, (i + n - 1) % n, iINF, 1);

    cout << mcf.flow(n, n + 1).second;
}
/* ╚══════════ /SOLVE ══════════╝ */
