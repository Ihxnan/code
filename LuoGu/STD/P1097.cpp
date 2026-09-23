#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    map<int, int> cnt;
    int n;
    cin >> n;
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++cnt[t];
    for (auto &[k, v] : cnt)
        cout << k << ' ' << v << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
