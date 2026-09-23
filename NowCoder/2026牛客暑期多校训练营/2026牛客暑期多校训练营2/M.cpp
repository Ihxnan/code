#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n, m;
    cin >> n >> m;
    if (m < n)
    {
        cout << m * (m - 1) / 2 << endl;
        return;
    }
    cout << (n - 1) * (n - 2) / 2 + n - m - 1 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
