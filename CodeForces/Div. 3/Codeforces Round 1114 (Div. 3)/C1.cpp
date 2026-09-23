#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    string a, b;
    cin >> n >> a >> b;

    int ca0 = 0, ca1 = 0, cb0 = 0, cb1 = 0;
    for (int i = 0; i < n; i += 2)
    {
        ca0 += a[i] == '1';
        cb0 += b[i] == '1';
        if (i + 1 < n)
        {
            ca1 += a[i + 1] == '1';
            cb1 += b[i + 1] == '1';
        }
    }

    if (ca0 == cb0 && ca1 == cb1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
