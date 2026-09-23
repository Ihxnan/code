#include <ihxnan>
#include <SegmentTree>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ul> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i] >> b[i], a[i] += a[i - 1], b[i] += b[i - 1];
    SegmentTree<ul> X(n), XD(n);
    for (ul i = 0, op, l, r, x; i < m; ++i)
    {
        cin >> op >> l >> r;
        if (op == 1)
        {
            cin >> x;
            X.update(l, r, x);
            XD.update(l, r, x * i);
        }
        else
        {
            ul x = X.query(l, r), xd = XD.query(l, r), A = a[r] - a[l - 1], B = b[r] - b[l - 1];
            cout << i * x - xd + A + B * (i + 1) << endl;
        }
    }
}
