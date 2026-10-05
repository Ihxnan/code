#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> m >> n;
    cout << (m % n == 0 ? 1 : 0) << endl;
}
