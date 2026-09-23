#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
#undef cout
void solve()
{
    int n;
    cin >> n;
    double r = 0.046;

    cout << 2 * n << endl;

    int rows = ceil(sqrt(n));
    int cols = (n + rows - 1) / rows;

    vector<double> xs(cols), ys(rows);
    for (int i = 0; i < cols; ++i)
        xs[i] = (cols == 1 ? 0.0 : -r + i * (2.0 * r / (cols - 1)));
    for (int j = 0; j < rows; ++j)
        ys[j] = (rows == 1 ? 0.0 : -r + j * (2.0 * r / (rows - 1)));

    for (int k = 0; k < n; ++k)
        cout << fixed << setprecision(9) << xs[k % cols] << ' ' << ys[k / cols] << ' ' << 0.5 << endl
             << fixed << setprecision(9) << xs[k % cols] << ' ' << ys[k / cols] << ' ' << -0.5 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
