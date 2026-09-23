#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    read(arr);
    cout << gcd(arr.front(), arr.back()) << endl;
}
