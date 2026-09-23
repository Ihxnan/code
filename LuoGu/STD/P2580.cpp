#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <StrHash>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    map<ul, int> cnt;
    string str;
    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        StrHash hash(str);
        cnt[hash.full()] = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> str;
        StrHash hash(str);
        ul tmp = hash.full();
        if (cnt.count(tmp) == 0)
            cout << "WRONG" << endl;
        else if (++cnt[tmp] == 1)
            cout << "OK" << endl;
        else
            cout << "REPEAT" << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
