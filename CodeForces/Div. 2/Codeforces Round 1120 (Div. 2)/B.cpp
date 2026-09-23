#include <ihxnan>

int init = [] { return cin >> t, 0; }();

// 1 2 6
// 4 5 9
// 7 8 3
//
// 1 2 4
// 3 5 6
// 7 8 9

void solve()
{
    int n, k;
    cin >> n >> k;
    if (k < n || k > 2 * n - 1)
        return cout << -1 << endl, void();
    vvi mat(n + 1, vi(n + 1));
    for (int i = 1; i <= n; ++i)
        mat[i][i] = i;
    k -= n;
    int idx = 2;
    while (k--)
        swap(mat[idx][idx], mat[idx][1]), ++idx;
    int dn = n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (mat[i][j] == 0)
                mat[i][j] = ++dn;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << mat[i][j] << ' ';
        cout << endl;
    }
}
