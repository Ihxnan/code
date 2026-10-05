#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;

    int h1 = 0;
    map<int, int> h4;

    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        int cnt = 0;
        while (t != 4 && t != 1)
        {
            ++cnt;
            int sum = 0;
            while (t)
                sum += t % 10 * (t % 10), t /= 10;
            t = sum;
        }
        if (t == 4)
            ++h4[cnt % 8];
        else
            ++h1;
    }

    ll ans = h1 * (h1 - 1) / 2;
    for (auto &[k, v] : h4)
        ans += v * (v - 1) / 2;

    cout << ans << endl;
}
