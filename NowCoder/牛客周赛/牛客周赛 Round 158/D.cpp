#include <ihxnan>

void solve()
{
    ll n, k;
    cin >> n >> k;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    auto check = [&](int x) -> bool {
        ll res = 0;
        ll cnt = 0;
        vi memo(n + 1);
        for (int i = 1; i <= x; ++i)
        {
            cnt += memo[arr[i]];
            ++memo[arr[i]];
        }
        res = max(res, cnt);

        for (int i = x + 1; i <= n; ++i)
        {
            --memo[arr[i - x]];
            cnt -= memo[arr[i - x]];
            cnt += memo[arr[i]];
            ++memo[arr[i]];
            res = max(res, cnt);
        }

        return res >= k;
    };

    int l = 0, r = n + 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
    cout << (r == n + 1 ? -1 : r) << endl;
}
