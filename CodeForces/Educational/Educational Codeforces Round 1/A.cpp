#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n;
    cin >> n;
    ll ans = (n + 1) * n / 2;
    ll sum = 0;
    ll t = 0;
    while ((1 << t) <= n)
        sum += 1 << t++;
    cout << ans - 2 * sum << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
