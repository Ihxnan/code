#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll x, y, n, m;
    cin >> x >> y >> n >> m;
    vl a(n), b(m);
    for (auto &p : a)
        cin >> p;
    for (auto &p : b)
        cin >> p;
    vl va(3), vb(3);
    if (n)
    {
        va[1] = *max_element(a.begin(), a.end());
        va[2] = *min_element(a.begin(), a.end());
    }
    if (m)
    {
        vb[1] = *max_element(b.begin(), b.end());
        vb[2] = *min_element(b.begin(), b.end());
    }
    ll ans = -lINF;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            ans = max(ans, (x + va[i]) * (y + vb[j]));
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
