#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    vvi cnt(30, vi(4));
    bitset<31> bit;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        t <<= 1;
        bit = t;
        for (int j = 0; j < 30; ++j)
            ++cnt[j][(bit[j + 1] << 1) + bit[j]];
    }
    int m;
    cin >> m;
    bitset<2> t;
    for (int i = 0, op, x; i < m; ++i)
    {
        cin >> op >> x;
        x <<= 1;
        bit = x;
        for (int j = 0; j < 30; ++j)
        {
            vi tmp(4);
            for (int k = 0; k < 4; ++k)
            {
                t = k;
                t[0] = op == 1 ? t[0] & bit[j] : op == 2 ? t[0] | bit[j] : t[0] ^ bit[j];
                t[1] = op == 1 ? t[1] & bit[j + 1] : op == 2 ? t[1] | bit[j + 1] : t[1] ^ bit[j + 1];
                tmp[t.to_ulong()] += cnt[j][k];
            }
            cnt[j] = tmp;
        }
        int ans = 0;
        for (int i = 0; i < 30; ++i)
            ans += cnt[i][2];
        cout << ans << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
