#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    vi b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];

    vi vec(n);
    auto check = [&](int x) -> bool {
        int cnt = 0;
        for (auto &p : a)
            cnt += p < x;

        for (int i = 0; i < n; ++i)
            if (a[i] >= x && b[i] < x)
                vec[i] = -1;
            else if (a[i] < x && b[i] >= x)
                vec[i] = 1;
            else
                vec[i] = 0;

        int dp = 0;
        for (int i = 0; i < n; ++i)
            dp = max(dp, dp + vec[i]);

        return cnt + dp > n / 2;
    };

    int l = 0, r = 1e9 + 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;

    cout << l << endl;
}
