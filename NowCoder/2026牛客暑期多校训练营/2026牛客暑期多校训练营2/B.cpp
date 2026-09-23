#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <LinearBasis>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n;
    cin >> n;
    ll sum = 0;
    vi arr(n);
    for (auto &p : arr)
        cin >> p, sum ^= p;
    ll bit = 31;

    gdb(sum);
    vl v;
    for (auto &p : arr)
    {
        ll t = 0;
        for (ll i = 0; i <= bit; ++i)
            if ((sum >> i & 1) == 0)
                t += p & (1 << i);
        v.push_back(t);
    }
    gdb(v);
    LinearBasis<ll> line;
    for (auto &p : v)
        line.insert(p);

    gdb(bit);
    ll ans = line.max() * 2;
    for (ll i = 0; i <= bit; ++i)
        if (sum >> i & 1)
            ans += sum & (1 << i);
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
