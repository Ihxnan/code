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
    vvl mp(n + 1, vl(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j];

    if (n == 1)
    {
        for (int i = 2; i <= m; ++i)
            if (mp[1][i] != mp[1][1])
            {
                cout << -1 << endl;
                return;
            }
        cout << 0 << endl;
        return;
    }

    if (m == 1)
    {
        for (int i = 2; i <= n; ++i)
            if (mp[i][1] != mp[1][1])
            {
                cout << -1 << endl;
                return;
            }
        cout << 0 << endl;
        return;
    }

    ll ult = mp[1][2] + mp[2][1] - mp[1][1];

    vvl sta(n + 1, vl(m + 1));
    sta[1][0] = lINF;

    for (int i = 1; i <= m; ++i)
    {
        sta[1][i] = ult - mp[1][i];
        sta[1][i - 1] -= sta[1][i];
        if (sta[1][i] < 0 || sta[1][i - 1] < 0)
        {
            cout << -1 << endl;
            return;
        }
    }
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            sta[i][j] = sta[i - 1][j];
            if (mp[i][j] + sta[i][j] > ult)
            {
                cout << -1 << endl;
                return;
            }
            sta[i][j - 1] -= ult - mp[i][j] - sta[i][j];
            sta[i][j] = ult - mp[i][j];
            if (sta[i][j] < 0 || sta[i][j - 1] < 0)
            {
                cout << -1 << endl;
                return;
            }
        }

    for (int i = 1; i < m; ++i)
        if (sta[n][i])
        {
            cout << -1 << endl;
            return;
        }

    cout << ult - mp[1][1] << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
