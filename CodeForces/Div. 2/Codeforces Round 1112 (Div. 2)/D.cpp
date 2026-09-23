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

    int ml = 0;
    vi arr(n + 1);
    for (int i = 1; i < n; ++i)
    {
        cin >> arr[i];
        if (arr[i] > arr[ml])
            ml = i;
    }
    if (arr[ml] != n - 1)
    {
        cout << 0 << endl;
        return;
    }
    int mr;
    for (int i = n - 1; i > 0; --i)
        if (arr[i] == arr[ml])
        {
            mr = i;
            break;
        }
    for (int i = ml + 1; i <= mr; ++i)
        if (arr[i] != arr[i - 1])
        {
            cout << 0 << endl;
            return;
        }
    for (int i = 2; i < ml; ++i)
        if (arr[i] < arr[i - 1])
        {
            cout << 0 << endl;
            return;
        }
    for (int i = n - 2; i > mr; --i)
        if (arr[i] < arr[i + 1])
        {
            cout << 0 << endl;
            return;
        }

    vi p(n + 1);
    vi sta(n + 1);
    sta[n] = sta[n - 1] = 1;
    for (int i = 1; i < ml; ++i)
        if (arr[i] > arr[i - 1])
        {
            p[i] = arr[i];
            if (++sta[arr[i]] > 1)
            {
                cout << 0 << endl;
                return;
            }
        }
    for (int i = n - 1; i > mr; --i)
        if (arr[i] > arr[i + 1])
        {
            p[i + 1] = arr[i];
            if (++sta[arr[i]] > 1)
            {
                cout << 0 << endl;
                return;
            }
        }
    for (int i = 1; i <= n; ++i)
        sta[i] += sta[i - 1];
    p[ml] = n;
    p[mr + 1] = n - 1;

    vi v;
    int ma;
    for (int i = 1; i < ml; ++i)
        if (p[i])
            ma = p[i];
        else
            v.push_back(ma);
    for (int i = n - 1; i > mr; --i)
        if (p[i + 1])
            ma = p[i + 1];
        else
            v.push_back(ma);
    for (int i = 0; i < mr - ml; ++i)
        v.push_back(n - 2);

    ll ans = 1;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
        ans = ans * (v[i] - sta[v[i]] - i) % mod;

    cout << 2 * ans % mod << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
