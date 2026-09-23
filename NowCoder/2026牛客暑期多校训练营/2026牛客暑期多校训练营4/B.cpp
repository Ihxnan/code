#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int p;
    cin >> p;
    ll x = sqrt(p) + 1;
    ll q = x * x - p;
    while (!(x % q && q % p))
        q = ++x * x - p;
    cout << x % q << ' ' << x % p << ' ' << q << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
