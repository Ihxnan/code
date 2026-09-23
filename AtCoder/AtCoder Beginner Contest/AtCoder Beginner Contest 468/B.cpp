#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int m, d;
    cin >> m >> d;
    string str;
    cin >> str;
    int cnt = 0;
    for (int i = 0; i < m; ++i)
        if (str[i] == '.')
        {
            bool flag = true;
            for (int j = i + 1; j <= i + d && j < m; ++j)
                if (str[j] == 'G')
                    flag = false;
            for (int j = i - 1; j >= i - d && j >= 0; --j)
                if (str[j] == 'G')
                    flag = false;
            cnt += flag;
        }
    cout << cnt << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
