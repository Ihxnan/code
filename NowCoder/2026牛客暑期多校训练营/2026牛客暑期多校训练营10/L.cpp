#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int m, r, c;
    cin >> m >> r >> c;
    double ans = 0;
    if (c <= m)
        ans = 1;
    else if (c <= 2 * m + r)
        ans = max(2.0 * m / (2 * m + r), 1.0 * m / c);
    else
    {
        int t = m, s = m;
        while (t < c)
        {
            if (t + r > c)
                break;
            t += r;

            t += m;
            s += m;
            if (t >= c)
                break;
        }
        ans = 1.0 * s / max(t, c);

        t = m, s = m;
        while (t < c)
            t += m + r, s += m;

        ans = max(ans, 1.0 * s / t);
    }
    printf("%.12f\n", ans);
}
