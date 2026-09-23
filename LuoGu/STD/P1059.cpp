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
    set<int> hash;
    for (int i = 0, t; i < n; ++i)
        cin >> t, hash.insert(t);
    cout << hash.size() << endl;
    for (auto &p : hash)
        cout << p << ' ';
}
/* ╚══════════ /SOLVE ══════════╝ */
