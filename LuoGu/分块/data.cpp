#include <ihxnan>
#include <Generator>

void solve()
{
    int n = g.rd(1, 1000);
    cout << n << endl;
    for (int i = 0; i < n; ++i)
        cout << g.rd(-3, 3) << ' ';
    cout << endl;
    for (int i = 0, l, r, c; i < n; ++i)
    {
        l = g.rd(1, n), r = g.rd(l, n);
        c = g.rd(-3, 3);
        cout << l << ' ' << r << ' ' << c << endl;
    }
}
