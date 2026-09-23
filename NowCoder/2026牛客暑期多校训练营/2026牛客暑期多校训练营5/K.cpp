#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k;
    cin >> n >> k;
    vi arr(n);
    for (auto &p : arr)
        cin >> p;

    auto mex = [](int x, int y, int z) -> int {
        vi arr{x, y, z};
        sort(arr.begin(), arr.end());
        int ans = 0;
        for (auto &p : arr)
            ans += ans == p;
        return ans;
    };

    map<vi, int> memo;
    int cnt = 0;
    memo[arr] = cnt++;

    while (k--)
    {
        vi tmp(n);
        for (int i = 0; i < n; ++i)
            tmp[i] = mex(arr[i], arr[(i + 1) % n], arr[(i + n - 1) % n]);
        arr = tmp;
        if (memo.count(arr))
            break;
        memo[arr] = cnt++;
    }

    if (k)
    {
        int idx = memo[arr];
        int d = cnt - idx;
        k %= d;
        idx += k;
        for (auto &[k, v] : memo)
            if (v == idx)
            {
                arr = k;
                break;
            }
    }

    for (auto &p : arr)
        cout << p << ' ';
}
/* ╚══════════ /SOLVE ══════════╝ */
