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
    string str;
    set<string> hash;
    for (int i = 0; i < n; ++i)
        cin >> str, hash.insert(str);
    cout << hash.size() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
