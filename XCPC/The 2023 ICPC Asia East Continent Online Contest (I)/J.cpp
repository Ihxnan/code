#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
const int N = 10;
double a[N], b[N];
double sx[N], sy[N];
double absd(double x)
{
    if (x < 0)
    {
        return x * -1.0;
    }
    else
        return x;
}
void solve()
{
    for (int i = 1; i <= 4; ++i)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= 2; ++i)
    {
        sx[i] = (a[i * 2 - 1] + a[i * 2]) / 2.0;
        sy[i] = (b[i * 2 - 1] + b[i * 2]) / 2.0;
    }
    double r = sqrt((a[4] - a[3]) * (a[4] - a[3]) + (b[4] - b[3]) * (b[4] - b[3])) / 2.0;
    double dx = sx[2] - sx[1];
    double dy = sy[2] - sy[1];
    double ans = dx + dy - sqrt(2.0) * r;

    cout << fixed << setprecision(10) << ans << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
