#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
int nxt[30][100001];
ll st[30][100001][6][6];

void solve()
{
    int n, c, q;
    cin >> n >> c >> q;
    int len = 30;
    for (int i = 1; i <= n; ++i)
        cin >> nxt[0][i];
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < c; ++j)
            for (int k = 0; k < c; ++k)
                cin >> st[0][i][j][k];

    ll res[6][6];
    auto mul = [&](ll a[6][6], ll b[6][6]) {
        for (int i = 0; i < c; ++i)
            for (int j = 0; j < c; ++j)
            {
                ll mi = lINF;
                for (int k = 0; k < c; ++k)
                    mi = min(mi, a[i][k] + b[k][j]);
                res[i][j] = mi;
            }
    };

    for (int i = 1; i < len; ++i)
        for (int j = 1; j <= n; ++j)
        {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
            mul(st[i - 1][j], st[i - 1][nxt[i - 1][j]]);
            for (int k = 0; k < c; ++k)
                for (int l = 0; l < c; ++l)
                    st[i][j][k][l] = res[k][l];
        }

    ll ans[6][6];
    for (int i = 0, x, k, s, t; i < q; ++i)
    {
        cin >> x >> k >> s >> t;

        for (int j = 0; j < c; ++j)
            for (int k = 0; k < c; ++k)
                ans[j][k] = j == k ? 0 : lINF;

        for (int i = 0; i < 30; ++i)
            if (k >> i & 1)
            {
                mul(ans, st[i][x]);
                for (int a = 0; a < c; ++a)
                    for (int b = 0; b < c; ++b)
                        ans[a][b] = res[a][b];
                x = nxt[i][x];
            }

        cout << ans[s][t] << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
