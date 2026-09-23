#include <algorithm>
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
    vi a(n), b(n);
    for (auto &p : a)
        cin >> p;
    for (auto &p : b)
        cin >> p;
    int cnt = 0;
    while (a < b)
        next_permutation(a.begin(), a.end()), ++cnt;
    cout << max(0, cnt - 1) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
