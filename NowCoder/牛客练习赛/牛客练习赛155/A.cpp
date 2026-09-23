#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    int cur = 10000 * a + 100 * b + c;
    if (cur == 20260109)
        cout << a << ' ' << b << ' ' << c << endl;
    else
        cout << "2026 1 8" << endl;
}
