#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cout
void solve()
{
    int n, k;
    string str;
    cin >> n >> k >> str;
    vi pos;
    for (int i = 0; i < n; ++i)
        if (str[i] == 'o')
            pos.push_back(i);
    auto check = [&](double mid) -> bool {
        double ma = -iINF;
        for (int r = 0; r < pos.size(); ++r)
        {
            if (r - k + 1 >= 0)
                ma = max(ma, mid * pos[r - k + 1] - (r - k + 1));
            if (ma >= mid * pos[r] - r + mid - 1)
                return true;
        }
        return false;
    };
    double l = 0, r = 1, mid;
    while (r - l > 1e-8)
        check(mid = (l + r) / 2) ? l = mid : r = mid;
    cout << fixed << setprecision(10) << r << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
