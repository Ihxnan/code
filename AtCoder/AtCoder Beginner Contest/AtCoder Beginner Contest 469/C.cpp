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
    str = '^' + str;
    vi hit(n + 1);
    for (int i = 1; i <= n; ++i)
        hit[i] = hit[i - 1] + (str[i] == 'o');
    bool flag = false;
    for (int i = 1; i <= n; ++i)
    {
        if (flag)
        {
            cout << n << endl;
            continue;
        }
        int res = i;
        int step = hit[i];
        while (step)
        {
            int t = res;
            res += step;
            if (res >= n)
            {
                flag = true;
                break;
            }
            step = hit[res] - hit[t];
        }
        if (flag)
        {
            cout << n << endl;
            continue;
        }
        cout << res << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
