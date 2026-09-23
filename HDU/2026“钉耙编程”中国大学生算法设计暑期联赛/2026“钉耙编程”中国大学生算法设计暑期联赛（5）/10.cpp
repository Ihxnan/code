#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
vi sg(101);
vvi basis(101);

void operator^=(vi &a, vi &b)
{
    for (int i = 0; i <= 100; ++i)
        a[i] ^= b[i];
}

bool insert(vi &x, int s)
{
    for (int i = 100; i >= 0; i--)
        if (x[i])
        {
            if (basis[i].empty())
            {
                sg[i] = s;
                basis[i] = x;
                return true;
            }
            s ^= sg[i];
            x ^= basis[i];
        }
    return false;
}

int find(vi &x)
{
    int ans = 0;
    for (int i = 100; i >= 0; i--)
        if (x[i])
        {
            if (basis[i].empty())
                return -1;
            ans ^= sg[i];
            x ^= basis[i];
        }
    return ans;
}

void solve()
{
    fill(sg.begin(), sg.end(), 0);
    fill(basis.begin(), basis.end(), vi());
    int k;
    cin >> k;
    for (int i = 0, c, s; i < k; ++i)
    {
        vi num(101);
        cin >> c >> s;
        for (int j = 0, t; j < c; ++j)
            cin >> t, num[t] ^= 1;
        insert(num, s);
    }

    int q;
    cin >> q;
    for (int i = 0, d; i < q; ++i)
    {
        vi num(101);
        cin >> d;
        for (int j = 0, t; j < d; ++j)
            cin >> t, num[t] ^= 1;
        cout << find(num) << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
