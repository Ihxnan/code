#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <Comb>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
Comb comb(mod);
void solve()
{
    ll w, l;
    cin >> w >> l;
    cout << (comb.qmi(w, l) + l - 1 + mod) % mod << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
