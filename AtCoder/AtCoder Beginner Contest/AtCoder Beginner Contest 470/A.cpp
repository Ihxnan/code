#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cout << (i % 3 ? to_string(i) : "Fizz") << endl;
}
