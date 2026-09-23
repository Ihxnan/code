#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    string s, t;
    cin >> n >> k >> s >> t;
    DSU dsu(n);
    for (int i = 0; i + k - 1 < n; ++i)
        dsu.merge(i, i + k - 1);
    map<int, array<int, 26>> a, b;
    for (int i = 0, r; i < n; ++i)
        ++b[r = dsu.get(i)][s[i] - 'a'], ++b[r = dsu.get(i)][t[i] - 'a'];
    cout << (a == b ? "Yes" : "No") << endl;
}
