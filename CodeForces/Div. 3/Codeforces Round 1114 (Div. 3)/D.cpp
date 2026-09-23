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
    map<ll, vi> hash;
    for (int i = 0; i < n; ++i)
        cin >> arr[i], hash[arr[i]].push_back(i);
    vector<pair<ll, vi>> v;
    for (auto &p : hash)
        v.push_back(p);
    vl ans(n);
    ll mi = 0;
    if (v[0].first)
    {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i < v.size() - 1; ++i)
    {
        ll tar = v[i + 1].first;
        ll dif = tar - v[i].first;
        if (dif % v[i].second.size())
        {
            cout << -1 << endl;
            return;
        }
        ll avg = dif / v[i].second.size();
        if (avg <= mi)
        {
            cout << -1 << endl;
            return;
        }
        for (auto &p : v[i].second)
            ans[p] = avg;
        mi = avg;
    }
    for (auto &p : ans)
        cout << (p ? p : mi + 1) << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
