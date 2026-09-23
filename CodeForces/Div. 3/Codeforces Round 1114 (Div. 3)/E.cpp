#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    multiset<ll> b;
    ll sum = 0;
    for (int i = 0, t; i < n; ++i)
        cin >> t, b.insert(t), sum += t;
    if (sum <= 0)
    {
        cout << -1 << endl;
        return;
    }
    vl ans(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        auto it = b.upper_bound(-ans[i - 1]);
        ans[i] = ans[i - 1] + *it;
        b.erase(it);
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
