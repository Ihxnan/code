#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m;
    cin >> n >> m;
    vi cnt(n + 1);
    map<pair<int, int>, int> hash;
    for (int i = 0, a, b; i < m; ++i)
    {
        cin >> a >> b;
        ++cnt[a], ++cnt[b];
        ++hash[{a, b}], ++hash[{b, a}];
    }

    set<pii> ans;
    for (int i = 1; i <= n; ++i)
        if (cnt[i] >= (m + 1) / 2)
            for (int j = 1; j <= n; ++j)
                if (i != j)
                    if (cnt[i] + cnt[j] - hash[{i, j}] == m)
                        ans.emplace(min(i, j), max(i, j));

    cout << ans.size() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
