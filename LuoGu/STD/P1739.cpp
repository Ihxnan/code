#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cin
void solve()
{
    char p;
    int stk = 0;
    while (cin >> p, p != '@')
        if (p == '(')
            ++stk;
        else if (p == ')' && --stk < 0)
        {
            cout << "NO" << endl;
            return;
        }
    if (stk)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
