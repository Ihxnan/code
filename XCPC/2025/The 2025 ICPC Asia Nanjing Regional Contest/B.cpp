#include <ihxnan>
#include <Point>

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

    vector<Point<ll>> vecs;
    for (int i = 0, a, b, c; i < n; ++i)
    {
        cin >> a >> b >> c;
        if (a || b)
            vecs.emplace_back(b, -a);
    }

    n = vecs.size();

    sort(vecs.begin(), vecs.end(), [](auto &a, auto &b) { return atan2l(a.y, a.x) < atan2l(b.y, b.x); });

    vecs.insert(vecs.end(), vecs.begin(), vecs.end());

    int ans = 0, idx = 0;
    for (int i = 0; i < n; ++i)
    {
        if (idx < i)
            idx = i;

        while (idx < i + n &&
               (cross(vecs[i], vecs[idx]) > 0 || cross(vecs[i], vecs[idx]) == 0 && dot(vecs[i], vecs[idx]) > 0))
            ++idx;
        ans = max(ans, idx - i);
    }

    cout << ans << endl;
}
