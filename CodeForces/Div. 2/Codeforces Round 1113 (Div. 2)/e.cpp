#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    lll n, m, d;
    cin >> n >> m >> d;
    vector<lll> p(m + 1), r(m + 1);
    for (int i = 1; i <= m; ++i)
        cin >> p[i] >> r[i], r[i] += r[i - 1];
    lll dayn = n * d + r[m];
    auto work = [&](lll x) -> lll {
        return x / n * dayn + x % n * d + r[upper_bound(p.begin(), p.end(), x % n) - p.begin() - 1];
    };
    for (int i = 1; i < m; ++i)
    {
        lll dayp = p[i] * d + r[i];
        for (int j = 1; j < m; ++j)
            if (dayp + p[j] * d + r[j] > work(p[i] + p[j] + 1))
            {
                cout << "YES" << endl;
                return;
            }
    }
    cout << "NO" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */

