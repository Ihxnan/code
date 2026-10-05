#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl v(n), l(n);
    rd0(v);
    rd0(l);
    sort(v.begin(), v.end());
    sort(l.rbegin(), l.rend());

    vl prev(n + 1), prel(n + 1);
    for (int i = 1; i <= n; ++i)
        prev[i] = prev[i - 1] + v[i - 1], prel[i] = prel[i - 1] + l[i - 1];

    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;

        auto check = [&](int x) -> bool { return v[x] > l[x] * t; };

        int l = -1, r = n, mid;
        while (l + 1 < r)
            check(mid = l + r) ? r = mid : l = mid;

        cout << prev[n] - prev[r] - prel[n] * t + prel[r] * t << ' ';
    }
    cout << endl;
}
