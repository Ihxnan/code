#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cin
void solve()
{
    stack<int> stk;
    int x;
    char op;
    cin >> x;
    stk.push(x);
    while (cin >> op >> x)
        if (op == '+')
            stk.push(x);
        else
            stk.top() = stk.top() * x % 10000;
    while (stk.size() > 1)
    {
        x = stk.top();
        stk.pop();
        stk.top() = (stk.top() + x) % 10000;
    }
    cout << stk.top() % 10000 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
