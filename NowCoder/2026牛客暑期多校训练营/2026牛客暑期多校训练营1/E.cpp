#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll i = 0, w = 1 - n, t; i < n; ++i, w += 2)
    {
        cin >> t;
        ans += t * w;
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
