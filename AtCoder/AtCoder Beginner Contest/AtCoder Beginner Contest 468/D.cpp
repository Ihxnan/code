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
    int n = str.size();
    ll ans = 0;
    for (int i = 0, l = 0, r = 0; i < n; l = r = ++i)
    {
        int d = 0;
        while (l >= 0 && r < n)
        {
            if ((d += str[l--] != str[r++]) > 1)
                break;
            ++ans;
        }
    }
    for (int i = 0, l = 0, r = 1; i < n - 1; l = ++i, r = l + 1)
    {
        int d = 0;
        while (l >= 0 && r < n)
        {
            if ((d += str[l--] != str[r++]) > 1)
                break;
            ++ans;
        }
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
