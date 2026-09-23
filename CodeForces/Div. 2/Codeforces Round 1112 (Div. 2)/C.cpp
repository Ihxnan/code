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
    vector<tuple<int, int, int, int>> arr(n);
    for (auto &[l, r, u, v] : arr)
        cin >> l >> r >> u >> v;
    auto check = [&](int m) -> bool
    {
        int left = 1, right = m;
        for (auto &[l, r, u, v] : arr)
            if (!(l <= left && left <= r) && !(u <= right && right <= v))
                ++left, --right;
        return left > m;
    };
    int ans = 0;
    for (int i = 0; i <= n; ++i)
        if (check(i))
            ans = i;
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
