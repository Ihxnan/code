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
    string str;
    cin >> str;
    str += str.substr(0, 11);
    string temp = "000100100000";
    size_t idx = 0;
    vi cnt(4);
    while ((idx = str.find(temp, idx)) != string::npos)
        ++cnt[idx++ % 4];
    int ans = 0;
    for (auto &p : cnt)
        if (p == 1)
            ans += n - 2;
        else if (p)
            ans += n;
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
