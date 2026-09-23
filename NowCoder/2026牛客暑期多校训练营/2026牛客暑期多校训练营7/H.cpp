#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    if (n & 1)
    {
        cout << 3 * n - 1 << ' ' << 0 << ' ' << n + n / 2 << endl;
        for (int i = 1; i <= n / 2; ++i)
            cout << n + n / 2 + i << ' ' << 2 * i << ' ' << n + n / 2 - i << endl
                 << 2 * n + n / 2 + i - 1 << ' ' << 2 * i - 1 << ' ' << 2 * n + n / 2 - i << endl;
    }
    else
    {
        cout << 2 * n + n / 2 << ' ' << n << ' ' << n + n / 2 << endl << n + n / 2 + 1 << ' ' << 0 << ' ' << 1 << endl;
        for (int i = 1; i < n / 2; ++i)
            cout << 2 * n + n / 2 + i << ' ' << 2 * i << ' ' << 2 * n + n / 2 - i << endl
                 << n + n / 2 + i + 1 << ' ' << 2 * i + 1 << ' ' << n + n / 2 - i << endl;
    }
}
