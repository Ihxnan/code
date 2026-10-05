#include <iostream>

using namespace std;
using ll = long long;

int exgcd(int a, int b, ll &x, ll &y) // 求 gcd(a,b) 与一组解 x, y
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); // 递归时交换 x/y
    y -= a / b * x;
    return d;
}

void solve()
{
    int a, b;
    ll x, y;
    cin >> a >> b;
    exgcd(a, b, x, y);
    if (x > 0)
        x %= b;
    if (x < 0)
        x = (abs(x) + b - 1) / b * b + x;
    if (x == 0)
        x = b;
    cout << x << endl;
}

int main()
{
    int t = 1;
    //	cin >> t;
    while (t--)
        solve();
    return 0;
}
