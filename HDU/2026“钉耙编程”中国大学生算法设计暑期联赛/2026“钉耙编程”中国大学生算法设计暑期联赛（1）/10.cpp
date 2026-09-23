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
    vl arr(n);
    for (auto &p : arr)
        cin >> p;
    if (n == 1)
    {
        cout << "NO" << endl;
        return;
    }
    if (n == 2)
    {
        cout << "YES" << endl;
        return;
    }
    if (n & 1)
    {
        ll sl = 0, sr = 0;
        for (int i = 0; i < n / 2; ++i)
            sl += arr[i];
        for (int i = n / 2 + 1; i < n; ++i)
            sr += arr[i];
        if (sl > sr)
            cout << "YES" << endl;
        else if (sl == sr)
        {
            int l = n / 2 - 1, r = n / 2 + 1;
            while (l >= 0 && sl == sr)
                sl -= arr[l--], sr -= arr[r++];
            if (l >= 0 && sl > sr)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else
            cout << "NO" << endl;
        return;
    }
    ll sl = 0, sr = 0;
    for (int i = 0; i < n / 2; ++i)
        sl += arr[i];
    for (int i = n / 2 + 1; i < n; ++i)
        sr += arr[i];
    if (sl > sr)
        cout << "YES" << endl;
    else if (sl == sr)
    {
        int l = n / 2 - 1, r = n / 2 + 1;
        while (r < n && sl == sr)
            sl -= arr[l--], sr -= arr[r++];
        if (r < n && sl < sr)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    else
        cout << "NO" << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
