#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    string str;
    cin >> n >> str;
    str = 'x' + str + 'x';
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (str[i] == 'x' && str[i - 1] == 'x' && str[i + 1] == 'x')
            ++cnt;
    cout << cnt << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
