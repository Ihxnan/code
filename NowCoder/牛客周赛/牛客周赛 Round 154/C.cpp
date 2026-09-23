#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k;
    cin >> n >> k;
    n -= k;
    string str;
    cin >> str;
    int x = 0, y = 0;
    for (auto &p : str)
        if (p == 'U')
            ++y;
        else if (p == 'D')
            --y;
        else if (p == 'L')
            --x;
        else
            ++x;

    gdb(x, y);

    string ans;
    for (auto &p : str)
    {
        gdb(ans);
        if (p == 'U')
        {
            if (y >= 0)
                ans += p;
            else
            {
                if (k > 0)
                    --k;
                else
                    ans += p;
            }
        }
        else if (p == 'D')
        {
            if (y < 0)
                ans += p;
            else
            {
                if (k > 0)
                    --k;
                else
                    ans += p;
            }
        }
        else if (p == 'L')
        {
            if (x <= 0)
                ans += p;
            else
            {
                if (k > 0)
                    --k;
                else
                    ans += p;
            }
        }
        else
        {
            if (x > 0)
                ans += p;
            else
            {
                if (k > 0)
                    --k;
                else
                    ans += p;
            }
        }
    }
    cout << ans.substr(0, n) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
