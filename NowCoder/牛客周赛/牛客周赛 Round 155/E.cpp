#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll k, q;
    cin >> k >> q;
    while (q--)
    {
        ll l, r, h, z;
        cin >> l >> r >> h >> z;
        ll pref = 0, cur = 0;
        for (int i = 0; i < h; ++i)
            cur ^= (z >> i) & 1, pref = (pref << 1) | cur;
        ll len = 1LL << (k - h), L = pref * len + 1, R = (pref + 1) * len;
        cout << max(0ll, min(r, R) - max(l, L) + 1) << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
