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
    string str;
    cin >> str;
    vi arr;
    for (int i = 0; i < n; ++i)
        if (str[i] == '1')
            arr.push_back(i);
    auto work = [&](string str, int idx) -> int {
        int i = 0;
        for (; i <= idx; ++i)
            if (str[i] == '1')
                str[i] = 'u';
        for (; i < n; ++i)
            if (str[i] == '1')
                str[i] = 't';
        gdb(str);
        int u = 0, us = 0, uss = 0, usst = 0;
        for (auto &p : str)
            if (p == 'u')
                ++u;
            else if (p == 's')
            {
                if (us)
                    --us, ++uss;
                else if (u)
                    --u, ++us;
            }
            else if (uss)
                --uss, ++usst;
        gdb(usst);
        return usst;
    };
    auto check = [&](int mid) -> bool { return work(str, arr[mid]) > work(str, arr[mid + 1]); };
    int l = -1, r = arr.size() - 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
    gdb(r);
    gdb(work(str, -1));
    cout << max({work(str, -1), work(str, n - 1), arr.size() ? work(str, arr[r]) : 0}) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
