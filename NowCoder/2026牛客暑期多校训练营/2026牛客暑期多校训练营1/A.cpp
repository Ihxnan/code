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
    vector<string> arr(n);
    set<char> hash{'a', 'e', 'i', 'o', 'u'};
    auto check = [&](string &str) -> bool {
        if (str.size() != 8)
            return false;
        for (int i = 0; i < 8; i += 2)
            if (hash.count(str[i]))
                return false;
        for (int i = 1; i < 8; i += 2)
            if (!hash.count(str[i]))
                return false;
        return true;
    };
    for (auto &p : arr)
    {
        cin >> p;
        if (!check(p))
            cout << "Well-Being" << endl;
        else
            cout << "Suspected Virus" << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
