#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
#undef cout
    int n, m;
    cin >> n >> m;
    ll delta = 0;
    bool flip = false;
    multiset<ll> small, big;

    auto get = [&](ll x) { return (flip ? -x : x) + delta; };

    auto insert = [&](ll x) {
        x = flip ? delta - x : x - delta;
        if (small.empty() || x <= *--small.end())
            small.insert(x);
        else
            big.insert(x);
        while (small.size() > big.size() + 1)
            big.insert(*--small.end()), small.erase(--small.end());
        while (big.size() > small.size())
            small.insert(*big.begin()), big.erase(big.begin());
    };

    for (int i = 1, t; i <= n; ++i)
        cin >> t, insert(t);

    auto print = [&] {
        if (small.size() == big.size())
            cout << fixed << setprecision(10) << (get(*--small.end()) + get(*big.begin())) / 2.0 << endl;
        else
            cout << get(*--small.end()) << endl;
    };

    print();

    for (int i = 0, op, k; i < m; ++i)
    {
        cin >> op >> k;
        if (op == 1)
            insert(k);
        else if (op == 2)
            delta += k;
        else
            flip = !flip, delta = 2 * k - delta;
        print();
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
