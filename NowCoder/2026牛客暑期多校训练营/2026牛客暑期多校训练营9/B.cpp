#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vi row(n + 1), col(n + 1);
    for (int i = 0, x, y; i < m; ++i)
        cin >> x >> y, ++row[x], ++col[y];
    int mi = iINF;
    for (auto &p : row)
        mi = min(mi, n - p);
    for (auto &p : col)
        mi = min(mi, n - p);
    cout << mi << endl;
}
