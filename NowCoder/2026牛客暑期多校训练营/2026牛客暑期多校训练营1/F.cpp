#include <algorithm>
#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k, x;
    cin >> n >> k >> x;
    vi arr(n);
    for (auto &p : arr)
        cin >> p;
    int idx = 0;
    for (int i = 0; i < n; ++i)
        if (x == arr[i])
            idx = i;
    gdb(idx);
    for (int i = 0; i < n; ++i)
        cout << arr[((idx + i - k) % n + n) % n] << ' ';
}
/* ╚══════════ /SOLVE ══════════╝ */
