#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    string str;
    cin >> str;
    str = '^' + str;
    int m;
    cin >> m;
    for (int i = 0, l, r, k; i < m; ++i)
    {
        cin >> l >> r >> k;
        string tmp = str.substr(l, r - l + 1);
        k %= tmp.size();
        for (int i = 0; i < tmp.size(); ++i)
            str[i + l] = tmp[(tmp.size() - k + i) % tmp.size()];
    }
    cout << str.substr(1) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
