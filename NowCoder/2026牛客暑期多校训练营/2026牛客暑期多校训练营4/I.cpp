#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    int k;
    string str;
    cin >> str >> k;
    n = str.size();
    string T = "Rounddo" + string(k, 'g');
    str += str.substr(0, T.size() - 1);
    gdb(str);
    size_t idx = 0;
    if ((idx = str.find(T, idx)) == string::npos)
    {
        gdb(1);
        cout << 0 << endl;
        return;
    }
    gdb(idx);
    if ((idx = str.find(T, idx + 1)) == string::npos)
    {
        gdb(2);
        cout << n + 1 - T.size() << endl;
        return;
    }
    gdb(3);
    cout << n << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
