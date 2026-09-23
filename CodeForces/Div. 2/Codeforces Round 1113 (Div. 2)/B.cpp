#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    for (auto &p : a)
        cin >> p;
    for (auto &p : b)
        cin >> p;

    if (n < 2 * m)
    {
        cout << "NO" << endl;
        return;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vb sta(n);

    int it = 0;
    int nx = n - m;
    for (int i = 0; i < m; ++i, ++it, ++nx)
        if (b[i] < a[it] || b[i] > a[nx])
        {
            cout << "NO" << endl;
            return;
        }

    cout << "YES" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
