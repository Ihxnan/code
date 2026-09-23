#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    auto work = [&](int a, int b) {
        if (!a || !b)
            return 0;
        return 2 * (a + b);
    };

    cout << work(x - 1, y - 1) + work(x - 1, m - y) + work(n - x, y - 1) + work(n - x, m - y) << endl;
}
