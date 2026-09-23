#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <DSU>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    DSU dsu(n);
    vl a(n), b(n), fa(n);
    for (auto &p : a)
        cin >> p;
    for (auto &p : b)
        cin >> p;
    for (auto &p : fa)
        cin >> p, --p;
    auto cmp = [](auto a, auto b) { return get<0>(a) * get<1>(b) < get<0>(b) * get<1>(a); };
    priority_queue<tl, vector<tl>, decltype(cmp)> que(cmp);
    for (int i = 0; i < n; ++i)
        que.emplace(a[i], b[i], i);
    ll ans = 0;
    while (que.size())
    {
        auto [ai, bi, idx] = que.top();
        que.pop();
        if (dsu.fa[idx] != idx)
            continue;
        if (fa[idx] != -1)
        {
            int root = dsu.get(fa[idx]);
            ans += a[idx] * b[root];
            dsu.fa[idx] = dsu.fa[root];
            a[root] += a[idx];
            b[root] += b[idx];
            que.emplace(a[root], b[root], root);
        }
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
