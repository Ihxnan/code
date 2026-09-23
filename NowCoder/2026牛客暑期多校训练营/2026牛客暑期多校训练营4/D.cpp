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
    cout << 1 << ' ';
    if (n == 1)
    {
        cout << endl;
        return;
    }
    if (n % 2)
    {
        cout << (n + 1) / 2 + 1 << ' ' << 2 << ' ';
        int up = (n + 1) / 2 + 2;
        int down = (n + 1) / 2;
        while (up <= n)
            cout << down-- << ' ' << up++ << ' ';
    }
    else
    {
        cout << n / 2 + 1 << ' ';
        int up = n / 2 + 2;
        int down = n / 2;
        while (up <= n)
            cout << down-- << ' ' << up++ << ' ';
    }
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
