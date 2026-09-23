#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    lll n, m, k;
    cin >> n >> m >> k;

    auto check2 = [&](lll n, lll x, lll val) -> bool { return n * n - x * x >= val; };

    auto lower = [&](lll n, lll x) -> int {
        lll l = 0, r = m + 1, mid;
        while (l + 1 < r)
            check2(n, mid = l + r >> 1, x) ? l = mid : r = mid;
        return l;
    };

    auto check1 = [&](lll x) -> bool {
        lll cnt = 0;
        for (lll i = 1; i <= n; ++i)
            cnt += lower(i, x);
        return cnt >= k;
    };

    lll l = -m * m, r = n * n, mid;
    while (l + 1 < r)
        check1(mid = l + r >> 1) ? l = mid : r = mid;

    vector<lll> arr{0};
    for (lll i = 1; i <= m; ++i)
        arr.push_back(arr.back() + i * i);

    lll ans = 0, cnt = 0;
    for (lll i = 1, t; i <= n; ++i)
    {
        cnt += t = lower(i, l);
        ans += i * i * t - arr[t];
    }

    cout << ans - (cnt - k) * l << endl;
}
