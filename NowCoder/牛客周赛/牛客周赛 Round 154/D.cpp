#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <SegmentTree>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, q;
    cin >> n >> q;
    SegmentTree<int> segt(n);
    string str;
    cin >> str;
    int ans = str[0] != str[n - 1];
    for (int i = 1; i < n; ++i)
        ans += str[i] != str[i - 1];
    str = '^' + str;
    for (int i = 0, l, r; i < q; ++i)
    {
        cin >> l >> r;
        ++l, ++r;
        if (l <= r)
            segt.update(l, r, 1, 1, n, 1);
        else
            segt.update(l, n, 1, 1, n, 1), segt.update(1, r, 1, 1, n, 1);
        if (r + 1 != l && !(l == 1 && r == n))
        {
            bool fl = segt.query(l, l, 1, 1, n) % 2, fr = segt.query(r, r, 1, 1, n) % 2;
            int ll = l - 1 ? l - 1 : n, rr = r + 1 > n ? 1 : r + 1;
            bool nl = segt.query(ll, ll, 1, 1, n) % 2, nr = segt.query(rr, rr, 1, 1, n) % 2;
            gdb(nl, fl, fr, nr);
            if (fl == nl && str[l] != str[ll] || fl != nl && str[l] == str[ll])
                ++ans;
            else
                --ans;
            if (fr == nr && str[r] != str[rr] || fr != nr && str[r] == str[rr])
                ++ans;
            else
                --ans;
        }
        cout << ans << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
