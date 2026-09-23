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
    string s, t;
    cin >> s >> t;
    s = '^' + s;
    t = '^' + t;
    vi d10(n + 1), d01(n + 1), same(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        d10[i] = d10[i - 1];
        d01[i] = d01[i - 1];
        same[i] = same[i - 1];
        if (s[i] == t[i])
            ++same[i];
        else if (s[i] == '0')
            ++d01[i];
        else
            ++d10[i];
    }
    int c01, c10, sm;
    for (int i = 0, l, r; i < q; ++i)
    {
        cin >> l >> r;
        c01 = d01[r] - d01[l - 1];
        c10 = d10[r] - d10[l - 1];
        sm = same[r] - same[l - 1];
        if (sm >= abs(c01 - c10))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
