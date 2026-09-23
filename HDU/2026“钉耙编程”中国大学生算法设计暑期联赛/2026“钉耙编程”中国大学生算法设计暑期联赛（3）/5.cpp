#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <PollarRho>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n;
    cin >> n;
    map<int, int> cnt;
    for (auto &p : factorize(n))
        ++cnt[p];
    int ma = 0;
    for (auto &[_, p] : cnt)
        ma = max(ma, p);
    cout << __lg(ma) + 1 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
