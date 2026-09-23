#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    vl arr;
    for (ll i = 0; i < n; ++i)
        if (str[i] == '0')
        {
            ll cnt = 1;
            while (str[i + 1] == '0')
                ++cnt, ++i;
            arr.push_back(cnt);
        }
    auto work = [&](ll n, ll now) {
        ll len = (n - now) / (now + 1);
        ll big = (n - now) % (now + 1);
        ll ans = big * (25 + len * 5);
        ans += (now + 1) * ((1 + len) * len / 2 * 5 + len * 20);
        return ans;
    };
    vl v(arr.size());
    priority_queue<pll> que;
    for (ll i = 0; i < arr.size(); ++i)
        que.emplace(work(arr[i], v[i]) - work(arr[i], v[i] + 1), i);
    while (k-- && que.size())
    {
        ll x = que.top().second;
        ++v[x];
        que.pop();
        if (v[x] + 1 <= arr[x])
            que.emplace(work(arr[x], v[x]) - work(arr[x], v[x] + 1), x);
    }
    ll ans = 0;
    for (ll i = 0; i < arr.size(); ++i)
        ans += work(arr[i], v[i]);
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
