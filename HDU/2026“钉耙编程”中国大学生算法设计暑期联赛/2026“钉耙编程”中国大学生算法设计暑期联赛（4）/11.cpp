#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, q;
    cin >> n >> q;
    vi arr(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], cnt += arr[i];

    vvi adj(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v;

    for (int i = 0, r; i < q; ++i)
    {
        cin >> r;
        if (arr[r] == 1)
            cout << 0 << endl;
        else
            cout << cnt + 1 << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
