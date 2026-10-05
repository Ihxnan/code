#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    cout << (k - 1) * 2 + (1ll << (n - k + 1)) << endl;
}
