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
    vi arr(n + 2);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    gdb(arr);
    if (n & 1)
    {
        cout << "NO" << endl;
        return;
    }
    int l = 0, r = 1e9 + 1;
    for (int i = 1; i < n; i += 2)
        l = max(l, arr[i + 1] + 1), r = min(r, arr[i] - 1);
    gdb(l, r);
    if (l <= r)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
