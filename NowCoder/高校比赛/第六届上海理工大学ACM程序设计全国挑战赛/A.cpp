#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    map<int, int> hash;
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++hash[t];
    cout << min({hash[0], hash[1], hash[2]}) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
