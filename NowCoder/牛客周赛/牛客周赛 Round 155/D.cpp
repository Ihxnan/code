#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n, m;
    cin >> n >> m;
    map<ll, ll> hash;
    vector<string> mp(n);
    for (auto &p : mp)
        cin >> p, ++hash[stoi(p, 0, 2)];

    ll cnt = 0;
    for (auto &[k1, v1] : hash)
        for (auto &[k2, v2] : hash)
            if ((k1 & k2) == 0)
                cnt += v1 * v2;

    cout << (n * (n - 1) - cnt) / 2 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
