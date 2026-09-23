#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    ll g = gcd(a, b);
    ll lcm = a * b / g;

    if (g > 1 || min(a, b) == 1 || lcm <= n)
        cout << b - a + m << endl;
    else
        cout << b - a + m * 2 << endl;
}
