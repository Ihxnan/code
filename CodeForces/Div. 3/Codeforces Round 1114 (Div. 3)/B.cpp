#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    string str;
    cin >> n >> str;
    int ma = 0;
    for (int i = 1; i < n - 1; ++i)
        if (str[i] != str[i - 1] && str[i] != str[i + 1])
        {
            if (str[i - 1] != str[i + 1])
                ma = max(ma, 1);
            else
                ma = max(ma, 2);
        }

    int cnt = 1;
    for (int i = 1; i < n; ++i)
        cnt += str[i] != str[i - 1];

    cout << cnt - ma << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
