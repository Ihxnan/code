#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n);

    int k = 0;
    for (int i = 0, a, b, d, x, y, z; i < m; ++i)
    {
        cin >> a >> b >> d;
        x = (a + k - 1) % n + 1;
        y = (b + k - 1) % n + 1;
        z = (d + k) % 1000000000 + 1;
        gdb(x, y, 2 * z);
        if (dsu.get(x) != dsu.get(y))
        {
            dsu.merge(x, y), ++k;
            cout << "Yes" << endl;
        }
    }
}
