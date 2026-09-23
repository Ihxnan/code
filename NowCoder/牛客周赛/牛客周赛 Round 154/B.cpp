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
    vi arr(n);
    iota(arr.begin(), arr.end(), 1);
    for (auto &p : arr)
        cout << p << ' ';
    cout << endl;
    reverse(arr.begin(), arr.end());
    for (auto &p : arr)
        cout << p << ' ';
}
/* ╚══════════ /SOLVE ══════════╝ */
