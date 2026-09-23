#include <ihxnan>

int init = [] { return cin >> t, 0; }();

bool is_prime(int x)
{
    if (x < 2)
        return false;
    for (int i = 2; i <= sqrt(x); ++i)
        if (x % i == 0)
            return false;
    return true;
}

void solve()
{
    TIME("solve");
    int n;
    cin >> n;
    for (int i = 0; i <= n; ++i)
        if (is_prime(i))
            cout << i << ' ';
}
