#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;
    vi a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i], b[a[i]] = i;
    for (int i = 0, op, x, y; i < q; ++i)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y;
            swap(a[x], a[y]);
            swap(b[a[x]], b[a[y]]);
        }
        else
            swap(a, b);
    }
    for (int i = 1; i <= n; ++i)
        cout << a[i] << ' ';
}
