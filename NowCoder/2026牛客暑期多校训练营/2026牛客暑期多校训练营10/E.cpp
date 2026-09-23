#include <ihxnan>

int init = [] { return cin >> t, 0; }();

using key = array<ll, 5>;
map<key, key> tr;

int bfs = [] {
    queue<key> que;

    for (int i = 0; i < 4; i += 2)
        for (int j = 0; j < 4; j += 2)
            for (int k = 0; k < 4; k += 2)
                for (int l = 0; l < 4; l += 2)
                    for (int m = 0; m < 4; m += 2)
                    {
                        key x{i, j, k, l, m};
                        tr[x] = x;
                        que.push(x);
                    }

    while (que.size())
    {
        key x = que.front();
        que.pop();
        for (int i = 0; i < 5; ++i)
            for (int j = i + 1; j < 5; ++j)
                for (int k = j + 1; k < 5; ++k)
                {
                    key y = x;
                    if (++y[i] >= 4 || ++y[j] >= 4 || ++y[k] >= 4 || tr.count(y))
                        continue;
                    bool flag = true;
                    tr[y] = tr[x], que.push(y);
                }
    }
    return 0;
}();

void solve()
{
    key arr;
    read(arr);
    sort(arr.rbegin(), arr.rend());
    key x(arr);
    for (auto &p : x)
        if (p & 1)
            p = min(p, 3ll);
        else
            p = min(p, 2ll);
    if (tr.count(x) == 0)
        return cout << -1 << endl, void();
    key y = tr[x];
    ll ans = 0;
    for (int i = 0; i < 5; ++i)
        ans += x[i] - y[i], arr[i] -= x[i] - y[i];
    ans /= 3;

    auto check = [&](ll x) -> bool {
        ll cnt = 0;
        for (int i = 0; i < 5; ++i)
            cnt += min(arr[i], x);
        return cnt >= 3 * x;
    };

    ll l = -1, r = 1e18, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? l = mid : r = mid;

    l -= l & 1;

    ll sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += arr[i];

    ans += l + (sum - 3 * l) / 2;
    cout << ans << endl;
}
