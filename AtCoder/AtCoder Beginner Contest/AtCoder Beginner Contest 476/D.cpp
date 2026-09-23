#include <ihxnan>

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;
    ll X, Y;
    cin >> X >> Y;
    vl a(n), b(m);
    rd0(a);
    rd0(b);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll cnt = 0, tmp = Y;
    for (int i = 0; i < m; ++i)
        if (tmp >= (b[i] + k - 1) / k)
            ++cnt, tmp -= (b[i] + k - 1) / k;

    auto work = [&](int x) -> int {
        ll b1 = X, bk = Y;
        for (int i = 0; i < x; ++i)
        {
            ll t = (b[i] + k - 1) / k;
            bk -= t;
            b1 += k * t - b[i];
        }
        b1 += bk * k;

        int res = x;
        for (int i = 0; i < n && b1 >= a[i]; ++i)
            b1 -= a[i], ++res;

        return res;
    };

    auto check = [&](int x) -> bool { return work(x) >= work(x + 1); };

    int l = -1, r = cnt - 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
    gdb(r);

    gdb(cnt);
    for (int i = 0; i <= cnt; ++i)
        gdb(i, work(i));

    cout << max(work(r), work(r + 1)) << endl;
}
