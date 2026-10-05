#include <ihxnan>

void solve()
{
    int n, d;
    int t = 0;
    while (cin >> n >> d, n && d)
    {
        vector<pii> in(n);
        for (auto &[x, y] : in)
            cin >> x >> y;
        bool flag = false;
        vector<pair<double, double>> arr;
        for (auto &[x, y] : in)
        {
            if (y > d)
            {
                flag = true;
                break;
            }
            double delta = sqrt(d * d - y * y);
            arr.emplace_back(x - delta, x + delta);
        }
        if (flag)
        {
            cout << "Case " << ++t << ": " << -1 << endl;
            continue;
        }
        sort(arr.begin(), arr.end(), [&](auto &x, auto &y) { return x.second < y.second; });
        int ans = 0;
        double last = -1e18;
        for (auto &[l, r] : arr)
            if (l > last)
            {
                last = r;
                ++ans;
            }
        cout << "Case " << ++t << ": " << ans << endl;
    }
}
