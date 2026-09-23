#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    ll sum = (1ll << k) - 1;
    vi a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    map<int, int> hash;
    for (int i = 1; i <= m; ++i)
        cin >> b[i], hash[b[i]] = i;
    vi c;
    for (int i = 1; i <= n; ++i)
        if (hash.count(sum ^ a[i]))
            c.push_back(hash[sum ^ a[i]]);
    vi dp;
    for (auto &p : c)
    {
        auto it = lower_bound(dp.begin(), dp.end(), p);
        if (it == dp.end())
            dp.push_back(p);
        else
            *it = p;
    }
    cout << dp.size() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
