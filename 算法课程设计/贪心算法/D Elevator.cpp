#include <ihxnan>

void solve()
{
    int n;
    while (cin >> n, n)
    {
        int ans = 0;
        int last = 0;
        for (int i = 0, t; i < n; ++i)
        {
            cin >> t;
            if (t > last)
                ans += (t - last) * 6 + 5;
            else
                ans += (last - t) * 4 + 5;
            last = t;
        }
        cout << ans << endl;
    }
}
