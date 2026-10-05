#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n;
    cin >> n;
    if (n & 1)
        cout << "No" << endl;
    else
        cout << "Yes" << endl << n / 2 << ' ' << n / 2 << endl;
}
