#include <iostream>

#define endl '\n'

using namespace std;
using ll = long long;

int exgcd(int a, int b, int &x, int &y) // 求 gcd(a,b) 与一组解 x, y
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
    ll a, b, c;
    cin >> a >> b >> c;
    if (c % __gcd(a, b))
        return cout << -1 << endl, void();
    int x, y;
    ll g = exgcd(a, b, x, y);
    ll bei = c / g;
    ll X = x * bei;
    ll Y = y * bei;
    ll A = b / g;
    ll B = a / g;
    if (X > 0)
        X %= A;
    if (X < 0)
        X = (abs(X) + A - 1) / A * A + X;
    if (X == 0)
        X = A;
    if (Y > 0)
        Y %= B;
    if (Y < 0)
        Y = (abs(Y) + B - 1) / B * B + Y;
    if (Y == 0)
        Y = B;
    ll Xx = X, Xy = (c - a * Xx) / b;
    ll Yy = Y, Yx = (c - b * Yy) / a;
    if (Xy <= 0)
        return cout << X << ' ' << Y << endl, void();
    cout << (Yx - X) / A + 1 << ' ' << X << ' ' << Y << ' ' << Yx << ' ' << Xy << endl;
}

int main()
{
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
