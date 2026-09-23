#include <ihxnan>
#include <Treap>

void solve()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    Treap<int> tr(n), tc(m);
    for (int i = 1; i <= n; ++i)
        tr.insert(i);
    for (int i = 1; i <= m; ++i)
        tc.insert(i);

    int t;
    char op;
    vi R(n + 1, iINF), C(m + 1, iINF);
    for (int i = 1; i <= k; ++i)
    {
        cin >> op >> t;
        if (op == 'C')
        {
            t = tc.val(t);
            C[t] = i, tc.erase(t);
        }
        else
        {
            t = tr.val(t);
            R[t] = i, tr.erase(t);
        }
    }

    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;
        cout << (min(R[x], C[y]) == iINF ? -1 : min(R[x], C[y])) << endl;
    }
}
