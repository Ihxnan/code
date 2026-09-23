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
    int mi = n, ma = 0;
    vvi arr(n + 1);
    for (int i = 1, t; i <= n; ++i)
        cin >> t, arr[t].push_back(i), mi = min(mi, t), ma = max(ma, t);
    if (n == 1)
    {
        cout << "Yes" << endl;
        return;
    }
    if (ma % 2 && arr[mi].size() != 1 || ma % 2 == 0 && arr[mi].size() != 2)
    {
        cout << "No" << endl;
        return;
    }

    for (int i = mi + 1; i <= ma; ++i)
        if (arr[i].size() < 2)
        {
            cout << "No" << endl;
            return;
        }

    cout << "Yes" << endl;

    if (ma % 2 == 0)
        cout << arr[mi][0] << ' ' << arr[mi][1] << endl;

    for (int i = mi + 1; i <= ma; ++i)
        for (int j = 0; j < arr[i].size(); ++j)
            cout << arr[i][j] << ' ' << arr[i - 1][j % arr[i - 1].size()] << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
