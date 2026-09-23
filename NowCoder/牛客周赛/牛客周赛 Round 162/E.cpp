#include <ihxnan>
#include <ST>

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    ST ma(arr), mi(arr, [&](int x, int y) { return min(x, y); });
    ma.init(), mi.init();
    int cnt = 0;
    for (int l = 1; l <= n; ++l)
        for (int r = l; r <= n; ++r)
        {
            int Ma = ma.query(l, r), Mi = mi.query(l, r);
            int m1, m2;
            if (l == 1)
                m1 = 0;
            else
                m1 = ma.query(1, l - 1);
            if (r == n)
                m2 = iINF;
            else
                m2 = mi.query(r + 1, n);
            cnt += m1 < Ma && Mi < m2;
        }
    cout << cnt << endl;
}
