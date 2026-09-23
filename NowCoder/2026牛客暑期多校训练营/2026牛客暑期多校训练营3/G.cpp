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

    map<int, vector<pii>> hash;
    for (int i = 1, t; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> t, hash[t].emplace_back(i, j);

    vvi ans(n + 2, vi(m + 2));
    auto work = [&](int x1, int y1, int x2, int y2) -> void {
        ++ans[x1][y1];
        --ans[x2 + 1][y1];
        --ans[x1][y2 + 1];
        ++ans[x2 + 1][y2 + 1];
    };

    for (auto &[num, arr] : hash)
    {
        vector<pii> left, right;
        left.emplace_back(arr.front());
        right.emplace_back(arr.back());
        for (int i = 1; i < arr.size(); ++i)
            if (arr[i].first != arr[i - 1].first && arr[i].second < left.back().second)
                left.emplace_back(arr[i]);
        for (int i = arr.size() - 2; i >= 0; --i)
            if (arr[i].first != arr[i + 1].first && arr[i].second > right.back().second)
                right.emplace_back(arr[i]);
        for (auto &[x1, y1] : left)
            for (auto &[x2, y2] : right)
                if (x1 < x2 && y1 < y2)
                    work(x1, y1, x2, y2);
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cout << ((ans[i][j] += ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1]) ? 1 : 0);
        cout << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
