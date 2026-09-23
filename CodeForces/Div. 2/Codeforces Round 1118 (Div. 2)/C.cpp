#include <ihxnan>

#undef endl
#undef cin
#undef cout
int init = [] {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return cin >> t, 0;
}();

void solve()
{
    int n;
    cin >> n;

    auto check = [&](int u, int v, int d) -> bool {
        int res;
        cout << '?' << ' ' << u << ' ' << v << ' ' << d << endl;
        cin >> res;
        return res;
    };

    int idx = 2, dist = 1;
    for (int i = 2; i <= n; ++i)
        while (check(1, i, dist + 1))
            idx = i, ++dist;

    int oth = 1;
    for (int i = 1; i <= n; ++i)
        if (i != idx)
            while (check(idx, i, dist + 1))
                oth = i, ++dist;

    cout << '!' << ' ' << idx << ' ' << oth << ' ' << dist << endl;
}
