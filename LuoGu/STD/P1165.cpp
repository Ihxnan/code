#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    stack<int> ma;
    stack<int> stk;
    for (int i = 0, op, x; i < n; ++i)
    {
        cin >> op;
        if (op == 0)
        {
            cin >> x;
            stk.push(x);
            if (ma.empty())
                ma.push(x);
            else
                ma.push(max(x, ma.top()));
        }
        else if (op == 1)
        {
            if (stk.size())
                stk.pop(), ma.pop();
        }
        else
        {
            if (stk.empty())
                cout << 0 << endl;
            else
                cout << ma.top() << endl;
        }
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
