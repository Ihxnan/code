#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <DSU>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, d;
    cin >> n >> d;
    DSU dsu(n);
    string str;
    cin >> str;
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < n / 2; ++i)
            dsu.merge((i + d * k) % n, (n - 1 - i + d * k) % n);
    map<int, string> hash;
    for (int i = 0; i < n; ++i)
        hash[dsu.get(i)] += str[i];
    int ans = 0;
    for (auto &[k, v] : hash)
    {
        map<char, int> cnt;
        for (auto &p : v)
            ++cnt[p];
        int ma = 0;
        for (auto &[k1, v1] : cnt)
            ma = max(ma, v1);
        ans += v.size() - ma;
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
