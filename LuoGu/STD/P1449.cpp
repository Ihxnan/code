#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cin
void solve()
{
    int x = 0;
    int tmp;
    char ch;
    stack<int> stk;
    while (cin >> ch, ch != '@')
        if (isdigit(ch))
            x = x * 10 + ch - '0';
        else if (ch == '.')
            stk.push(x), x = 0;
        else
        {
            tmp = stk.top();
            stk.pop();
            if (ch == '+')
                stk.top() += tmp;
            else if (ch == '-')
                stk.top() -= tmp;
            else if (ch == '*')
                stk.top() *= tmp;
            else if (ch == '/')
                stk.top() /= tmp;
        }
    cout << stk.top() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
