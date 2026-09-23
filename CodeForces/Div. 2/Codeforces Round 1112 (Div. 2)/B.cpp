#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */
/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k;
    cin >> n >> k;
    int t = k / 2, r = k % 2;
    string ans = string(t + 1, '0') + string(t + 1, '1');
    char ch = r ^ '1';
    while (ans.size() < n)
        ans += ch ^= 1;
    if (ans.size() != n)
        cout << -1 << endl;
    else
    {
        int cnt = 0;
        for (int i = 1; i < n; ++i)
            cnt += ans[i] == ans[i - 1];
        if (cnt == k)
            cout << ans << endl;
        else
            cout << -1 << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
