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
    int sz = n + 1 >> 1;
    vi ans(sz);
    for (int i = 0; i < sz; ++i)
        ans[i] = 2 * (sz - 1 - i) + 1;
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = i + 1; j < ans.size(); ++j)
            if (ans[i] % ans[j] == 0)
                ans[j] <<= 1;
        sort(ans.rbegin(), ans.rend());
    }
    sort(ans.begin(), ans.end());
    cout << sz << endl;
    for (auto &p : ans)
        cout << p << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
