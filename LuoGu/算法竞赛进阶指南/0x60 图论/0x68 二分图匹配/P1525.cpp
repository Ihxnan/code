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
    vector<ti> arr(m);
    for (auto &[a, b, c] : arr)
        cin >> a >> b >> c;
    auto check = [&](int mid) -> bool {
        vi poi;
        vvi adj(n + 1);
        for (auto &[a, b, c] : arr)
            if (c > mid)
                adj[a].push_back(b), adj[b].push_back(a), poi.push_back(a);
        if (poi.empty())
            return true;
        vi sta(n + 1);
        auto dfs = [&](auto &&self, int x, int color) -> bool {
            sta[x] = color;
            for (auto &p : adj[x])
            {
                if (!sta[p])
                {
                    if (self(self, p, 3 - color))
                        return true;
                }
                else if (sta[p] == color)
                    return true;
            }
            return false;
        };
        for (auto &p : poi)
            if (!sta[p])
                if (dfs(dfs, p, 1))
                    return false;
        return true;
    };
    int l = -1, r = 1e9 + 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
    cout << r << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
