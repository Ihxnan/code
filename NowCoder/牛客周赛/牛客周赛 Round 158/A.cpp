#include <ihxnan>

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    cout << 4 * abs(a - b) + 2 * abs(b - c) + abs(c - a);
}
