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
    ll n, m, c, a, b;
    cin >> n >> m >> c >> a >> b;
    if (n > m || (m - n) % c)
    {
        cout << 0 << endl;
        return;
    }
    int cnt = (m - n) / c;
    cout << comb.qmi(a, cnt) * comb.qmi(b - a, m - cnt) % mod * n % mod * comb.C(m, cnt) % mod *
                comb.inv(comb.qmi(b, m) * m % mod) % mod
         << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
