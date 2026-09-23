#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int k;
    cin >> k;
    // t * (t - 1) / 2
    int l = 0, r = 1e5, mid;
    auto check = [&](ll x) { return x * (x - 1) / 2 <= k; };
    while (l + 1 < r)
        check(mid = l + r >> 1) ? l = mid : r = mid;
    int b = k - l * (l - 1) / 2;
    gdb(l, b);
    cout << l + b << ' ' << 2 << endl;
    cout << string(l, 'a') << string(b, 'b') << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
