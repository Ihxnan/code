#include <ihxnan>
#include <Generator>

void solve()
{
    int t = g.rd(1, 1);
    while (t--)
    {
        int n = g.rd(10, 10);
        cout << n << endl;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                cout << g.rd(1, 1e3) << ' ';
            cout << endl;
        }
    }
}
